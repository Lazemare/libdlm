#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delimitedfiles.h"

/* Write delimited file. */
int writedlm(FILE *fp, struct DLM *dlm, char delim)
{
	int i,j;
	int flag = 0;
	int count = 0;

	for (i=0; i < (*dlm).linenum; i++) {
		flag = 0;
		for (j=0; j < MAXWORDS; j++) {
			if (strcmp((*dlm).list[i][j],"\0") > 0) {
				fprintf(fp,"%s%c",(*dlm).list[i][j],delim);
				flag = 1;
				count++;
			}
		}
		if (flag == 1) {
			fprintf(fp,"\n\n");
		}
	}
	return count;
}
