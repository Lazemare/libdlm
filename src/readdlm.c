#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readdlm.h"
#include "delimitedfiles.h"

/* initialization */
#define INIT_DLM(dlm) do { \
	dlm->list = (char ***) calloc((sizeof(char **)),1); \
	dlm->wordnum = (int *) calloc((sizeof(int)),1); \
	dlm->linenum = 1; \
	dlm->wordnum[0] = 0; \
} while (0)

/* append one blank line to dlm.list.  */
#define APPEND_DLM_LINE(dlm) do { \
	(dlm->linenum)++; \
	dlm->list = (char ***) realloc(dlm->list, \
		(dlm->linenum)*(sizeof(char **))); \
	memset(&(dlm->list[dlm->linenum-1]), 0, (sizeof(char **))); \
	dlm->wordnum = (int *) realloc(dlm->wordnum, \
		(dlm->linenum)*(sizeof(int))); \
	dlm->wordnum[dlm->linenum - 1] = 0; \
} while (0)

/* append one word to dlm.list[linenum-1] */
#define APPEND_DLM_WORD(dlm, buff) do { \
	(dlm->wordnum[dlm->linenum-1])++; \
	dlm->list[dlm->linenum-1] = (char **) realloc(dlm->list[dlm->linenum-1], \
		(dlm->wordnum[dlm->linenum-1])*(sizeof(char *))); \
	memset(&(dlm->list[dlm->linenum-1][dlm->wordnum[dlm->linenum-1]-1]), \
		0, (sizeof(char *))); \
	dlm->list[dlm->linenum-1][dlm->wordnum[dlm->linenum-1]-1] = \
		(char *) calloc(strlen(buff)+1, 1); \
	strcpy(dlm->list[dlm->linenum-1][dlm->wordnum[dlm->linenum-1]-1], buff); \
} while (0)

/* free struct DLM */
void free_dlm(dlm_t *dlm)
{
	int i, j;

	for (i = 0; i < dlm->linenum; i++) {
		for (j = 0; j < dlm->wordnum[i]; j++) {
			free(dlm->list[i][j]);
			dlm->list[i][j] = NULL;
		}
		free(dlm->list[i]);
		dlm->list[i] = NULL;
	}
	free(dlm->list);
	free(dlm->wordnum);
	dlm->list = NULL;
	dlm->wordnum = NULL;
	dlm->linenum = 0;
}

/* helper function of readdlm. */
static inline int readdlm_helper(char inp, int quotescue, char delim, \
	int quotes, int comments, char comment_char)
{
	/* 0 for same word, 1 for meet delimiter
	 * 2 for begin of quotes, 3 for end of quotes
	 * 4 for begin of comments, 5 for next line. */

	if (!quotes) {
		if (comments && inp == comment_char) {
			return 4;
		} else if (inp != delim && inp != LF && inp != CR) {
			return 0;
		} else if (inp == delim) {
			return 1;
		} else if (inp == LF || inp == CR) {
			return 5;
		}
	} else if (quotes && quotescue == 0) {
		if (comments && inp == comment_char) {
			return 4;
		} else if (inp != '"' && \
			(inp != delim && inp != LF && inp != CR)) {
			return 0;
		} else if (inp != '"' && inp == delim) {
			return 1;
		} else if (inp == '"') {
			return 2;
		} else if (inp == LF || inp == CR) {
			return 5;
		}
	} else if (quotes && quotescue == 1) {
		if (inp == '"') {
			return 3;
		} else if (inp != LF && inp != CR) {
			return 0;
		} else if (inp == LF || inp == CR) {
			return 5;
		}
	}
	return -1; /* Fatal */
}

/* Read delimited file into a 3D array. */
void readdlm(FILE *fp, dlm_t *dlm, char delim, int quotes, \
	int comments, char comment_char)
{
	size_t len;
	size_t read;
	int i, k;
	int code = 0;
	int wordcue = 0;
	int quotescue = 0;
	char *line = NULL;
	char buff[BUFFSIZE];
	memset(buff, 0, BUFFSIZE);
	INIT_DLM(dlm);

	/* Read in one line. */
	while ((read = getline(&line, &len, fp)) != EOF) {
		i = 0;
		k = 0;
		wordcue = 0;
		memset(buff, 0, BUFFSIZE);
		/* append one line if current line is not empty. */
		if (dlm->wordnum[dlm->linenum - 1]) {
			APPEND_DLM_LINE(dlm);
		}
		/* Make test of every letter in this line. */
		for (i = 0; i < read; i++) {
			code = readdlm_helper(line[i],quotescue, \
				delim,quotes,comments,comment_char);
			if (code == 4 && i == 0) {
				/* Line start with comment_char, skip all. */
				goto SKIP;
			} else if (code == 4 && wordcue == 1) {
				/* Find comment_char, skip to next line. */
				APPEND_DLM_WORD(dlm,buff);
				memset(buff, 0, BUFFSIZE);
				goto SKIP;
			} else if (code == 4 && wordcue == 0) {
				/* Find comment_char, skip to next line. */
				goto SKIP;
			} else if (code == 5 && (i == 0 || wordcue == 0)) {
				/* Blank line, skip to next line. */
				goto SKIP;
			} else if (code == 5 && i != 0) {
				/* Line terminal, append last word. */
				APPEND_DLM_WORD(dlm,buff);
				memset(buff, 0, BUFFSIZE);
				goto SKIP;
			} else if (code == 0) {
				buff[k] = line[i];
				wordcue = 1;
				k++;
			} else if (code == 1 && wordcue == 1) {
				k = 0; /* Meet delimiter */
				wordcue = 0;
				APPEND_DLM_WORD(dlm,buff); /* append last word. */
				memset(buff, 0, BUFFSIZE);
			} else if (code == 2) {
				quotescue = 1; /* Find quotation mark */
			} else if (code == 3) {
				quotescue = 0; /* Find quotation mark */
			}
		}
		SKIP:
			NULL;
	}
	free(line);
}
