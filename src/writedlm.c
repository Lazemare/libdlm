#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delimitedfiles.h"

/* Write delimited file. */
int writedlm(FILE *fp, char list[MAXLINES][MAXWORDS][MAXLETTERS], char delim)
{
	int i,j;
	int flag = 0;
	int count = 0;

	for (i=0; i < MAXLINES; i++) {
		flag = 0;
		for (j=0; j < MAXWORDS; j++) {
			if (strcmp(list[i][j],"\0") > 0) {
				fprintf(fp,"%s%c",list[i][j],delim);
				flag = 1;
				count++;
			}
		}
		if (flag == 1) {
			fprintf(fp,"\n");
		}
	}
	return count;
}
