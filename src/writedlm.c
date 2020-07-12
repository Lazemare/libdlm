#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delimitedfiles.h"

/* Write delimited file. */
int writedlm(FILE *fp, dlm_t *dlm, char delim)
{
	int i,j;
	int count = 0;

	for (i = 0; i < dlm->linenum; i++) {
		for (j = 0; j < dlm->wordnum[i]; j++) {
			fprintf(fp,"%s%c",dlm->list[i][j],delim);
			count++;
		}
		fprintf(fp,"\n");
	}
	return count;
}
