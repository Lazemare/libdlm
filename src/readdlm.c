#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delimitedfiles.h"

/* helper function of readdlm. */
static inline int readdlm_helper(char inp, int quotescue, char delim, \
	int quotes, int comments, char comment_char)
{
	/* 0 for same word, 1 for next word 
	   2 for begin of quotes, 3 for end of quotes 
	   4 for begin of comments, 5 for next line. */
	int code = 0;

	if (quotes == 1) {
		if (comments == 0 && inp == comment_char) {
			code = 4;
		} else if (inp != delim && inp != EOL) {
			code = 0;
		} else if (inp == delim) {
			code = 1;
		} else if (inp == EOL) {
			code = 5;
		}
	} else if (quotes == 0 && quotescue == 0) {
		if (comments == 0 && inp == comment_char) {
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
	} else if (quotes == 0 && quotescue == 1) {
		if (inp == '"' && inp != EOL) {
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
int readdlm(FILE *fp, char list[MAXLINES][MAXWORDS][MAXLETTERS], \
	char delim, int quotes, int comments, char comment_char)
{
	size_t len;
	size_t read;
	int i, j, k;
	int code = 0;
	int wordcue = 0;
	int linenum = 0;
	int quotescue = 0;
	char *line = NULL;
	/* Just in case ... */
	memset(list, 0, sizeof *list);

	/* Read in one line. */
	while ((read = getline(&line, &len, fp)) != -1) {
		i = 0; j = 0; k = 0; wordcue = 0;
		/* Make test of every letter in this line. */
		for (i=0; i < read; i++) {
			code = readdlm_helper(line[i],quotescue, \
				delim,quotes,comments,comment_char);
			if (code == 4 && i ==0) {
				goto SKIP;
			} else if (code == 4 || code == 5) {
				linenum++;
				goto SKIP;
			} else if (code == 0) {
				list[linenum][j][k] = line[i];
				wordcue = 1;
				k++;
			} else if (code == 1) {
				wordcue = 0;
				k = 0;
				j++;
			} else if (code == 2) {
				quotescue = 1;
			} else if (code == 3) {
				quotescue = 0;
			}
		}
		linenum++;
		SKIP:
			NULL;
	}
	return 0;
}
