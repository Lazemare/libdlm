#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delimitedfiles.h"

/* clean dlm.list */
static void memset_dlm(struct DLM dlm)
{
	int i, j;
	for (i = 0; i<MAXLINES; i++) {
		for (j = 0; j<MAXWORDS; j++) {
			memset(dlm.list[i][j], 0, MAXLETTERS*sizeof(char));
		}
	}
}

/* initialize dlm.list */
void init_dlm(struct DLM *dlm)
{
	(*dlm).list = (char***)malloc(MAXLINES*(sizeof(char**)));
	int i, j;
	for (i = 0; i<MAXLINES; i++) {
		(*dlm).list[i] =
			(char**)malloc(MAXWORDS*sizeof(char*));
		for (j = 0; j<MAXWORDS; j++) {
			(*dlm).list[i][j] =
				(char*)malloc(MAXLETTERS*sizeof(char));
		}
	}
}

/* free dlm.list */
void free_dlm(struct DLM *dlm)
{
	int i, j;
	for (i = 0; i < MAXLINES; i++) {
		for (j = 0; j<MAXWORDS; j++) {
			(*dlm).list[i][j] = NULL;
			free((*dlm).list[i][j]);

		}
		(*dlm).list[i] = NULL;
		free((*dlm).list[i]);

	}
	(*dlm).list = NULL;
	free((*dlm).list);
}


/* helper function of readdlm. */
static inline int readdlm_helper(char inp, int quotescue, char delim, \
	int quotes, int comments, char comment_char)
{
	/* 0 for same word, 1 for next word
	 * 2 for begin of quotes, 3 for end of quotes
	 * 4 for begin of comments, 5 for next line. */
	int code = 0;

	if (!quotes) {
		if (comments && inp == comment_char) {
			code = 4;
		} else if (inp != delim && inp != EOL) {
			code = 0;
		} else if (inp == delim) {
			code = 1;
		} else if (inp == EOL) {
			code = 5;
		}
	} else if (quotes && quotescue == 0) {
		if (comments && inp == comment_char) {
			code = 4;
		} else if (inp != '"' && (inp != delim && inp != EOL)) {
			code = 0;
		} else if (inp != '"' && inp == delim) {
			code = 1;
		} else if (inp == '"') {
			code = 2;
		} else if (inp == EOL) {
			code = 5;
		}
	} else if (quotes && quotescue == 1) {
		if (inp == '"') {
			code = 3;
		} else if (inp != EOL) {
			code = 0;
		} else if (inp == EOL) {
			code = 5;
		}
	}
	return code;
}

/* Read delimited file into a 3D array. */
void readdlm(FILE *fp, struct DLM *dlm, char delim, int quotes, \
	int comments, char comment_char)
{
	size_t len;
	size_t read;
	int i, j, k;
	int code = 0;
	int wordcue = 0;
	int quotescue = 0;
	char *line = NULL;
	(*dlm).linenum = 0;
	(*dlm).wordnum = 0;
	memset_dlm(*dlm);

	/* Read in one line. */
	while ((read = getline(&line, &len, fp)) != -1) {
		i = 0; j = 0; k = 0; wordcue = 0;
		/* Make test of every letter in this line. */
		for (i=0; i < read; i++) {
			code = readdlm_helper(line[i],quotescue, \
				delim,quotes,comments,comment_char);
			if (code == 4 && i == 0) {
				goto SKIP;
			} else if (code == 4) {
				(*dlm).linenum++;
				goto SKIP;
			} else if (code == 5) {
				(*dlm).linenum++;
				goto SKIP;
			} else if (code == 0) {
				(*dlm).list[(*dlm).linenum][j][k] = line[i];
				if (wordcue == 0) {
					wordcue = 1;
					(*dlm).wordnum++;
				}
				k++;
			} else if (code == 1 && wordcue == 1) {
				wordcue = 0;
				k = 0;
				j++;
			} else if (code == 2) {
				quotescue = 1;
			} else if (code == 3) {
				quotescue = 0;
			}
		}
		(*dlm).wordnum++;
		SKIP:
			NULL;
	}
}
