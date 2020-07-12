#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delimitedfiles.h"

#define DLM_COUNT(dlm,count) do { \
	count = 0; \
	for (int i = 0; i < dlm.linenum; i++) { \
		count += dlm.wordnum[i]; \
	} \
} while (0)

int main(int argc, char *argv[])
{
	FILE *inp = NULL;
	FILE *out = NULL;
	inp = fopen(argv[1],"r");
	out = fopen("out","w");
	int readnum = 0;
	int writenum = 0;
	dlm_t dlm;

	readdlm(inp,&dlm,' ',1,1,'#');
	DLM_COUNT(dlm,readnum);
	printf("---- quotes = 1; comments = 1; comment_char='#'; ----\n\n");
	fprintf(out,"---- quotes = 1; comments = 1; comment_char='#'; ----\n\n");
	writedlm(stdout,&dlm,' ');
	writenum = writedlm(out,&dlm,' ');
	fprintf(out,"%s %d\n","Total read-in words:",readnum);
	fprintf(out,"%s %d\n","Total write-out words:",writenum);
	printf("%s %d\n","Total read-in words:",readnum);
	printf("%s %d\n","Total write-out words:",writenum);
	fprintf(out,"-----------------------------------------------------\n\n");
	printf("-----------------------------------------------------\n\n");
	fflush(stdout);
	free_dlm(&dlm);

	rewind(inp);
	readdlm(inp,&dlm,' ',0,1,'#');
	DLM_COUNT(dlm,readnum);
	printf("---- quotes = 0; comments = 1; comment_char='#'; ----\n\n");
	fprintf(out,"---- quotes = 0; comments = 1; comment_char='#'; ----\n\n");
	writedlm(stdout,&dlm,' ');
	writenum = writedlm(out,&dlm,' ');
	fprintf(out,"%s %d\n","Total read-in words:",readnum);
	fprintf(out,"%s %d\n","Total write-out words:",writenum);
	printf("%s %d\n","Total read-in words:",readnum);
	printf("%s %d\n","Total write-out words:",writenum);
	fprintf(out,"-----------------------------------------------------\n\n");
	printf("-----------------------------------------------------\n\n");
	fflush(stdout);
	free_dlm(&dlm);

	rewind(inp);
	readdlm(inp,&dlm,' ',0,0,'#');
	DLM_COUNT(dlm,readnum);
	printf("------------- quotes = 0; comments = 0; -------------\n\n");
	fprintf(out,"------------- quotes = 0; comments = 0; -------------\n\n");
	writedlm(stdout,&dlm,' ');
	writenum = writedlm(out,&dlm,' ');
	fprintf(out,"%s %d\n","Total read-in words:",readnum);
	fprintf(out,"%s %d\n","Total write-out words:",writenum);
	printf("%s %d\n","Total read-in words:",readnum);
	printf("%s %d\n","Total write-out words:",writenum);
	fprintf(out,"-----------------------------------------------------\n\n");
	printf("-----------------------------------------------------\n\n");
	fflush(stdout);
	free_dlm(&dlm);

	rewind(inp);
	readdlm(inp,&dlm,' ',0,0,'#');
	DLM_COUNT(dlm,readnum);
	printf("--- quotes = 0; comments = 0; output delim = '\\t'; ---\n\n");
	fprintf(out,"--- quotes = 0; comments = 0; output delim = '\\t'; ---\n\n");
	writedlm(stdout,&dlm,'\t');
	writenum = writedlm(out,&dlm,'\t');
	fprintf(out,"%s %d\n","Total read-in words:",readnum);
	fprintf(out,"%s %d\n","Total write-out words:",writenum);
	printf("%s %d\n","Total read-in words:",readnum);
	printf("%s %d\n","Total write-out words:",writenum);
	fprintf(out,"-----------------------------------------------------\n");
	printf("-----------------------------------------------------\n");
	fflush(stdout);
	free_dlm(&dlm);

	fclose(inp);
	fclose(out);
	return 0;
}
