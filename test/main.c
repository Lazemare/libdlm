#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delimitedfiles.h"

int main(int argc, char *argv[])
{
	FILE *inp;
	FILE *out;
	inp = fopen(argv[1],"r");
	out = fopen("out","w");
	int i,j,writenum;
	int flag;
	struct DLM dlm;
	init_dlm(&dlm);

	readdlm(inp,&dlm,' ',1,1,'#');
	printf("---- quotes = 1; comments = 1; comment_char='#'; ----\n\n");
	fprintf(out,"---- quotes = 1; comments = 1; comment_char='#'; ----\n\n");
	writedlm(stdout,&dlm,' ');
	writenum = writedlm(out,&dlm,' ');
	fprintf(out,"%s %d\n","Total read-in words:",dlm.wordnum);
	fprintf(out,"%s %d\n","Total write-out words:",writenum);
	printf("%s %d\n","Total read-in words:",dlm.wordnum);
	printf("%s %d\n","Total write-out words:",writenum);
	fprintf(out,"-----------------------------------------------------\n\n");
	printf("-----------------------------------------------------\n\n");

	rewind(inp);
	readdlm(inp,&dlm,' ',0,1,'#');
	printf("---- quotes = 0; comments = 1; comment_char='#'; ----\n\n");
	fprintf(out,"---- quotes = 0; comments = 1; comment_char='#'; ----\n\n");
	writedlm(stdout,&dlm,' ');
	writenum = writedlm(out,&dlm,' ');
	fprintf(out,"%s %d\n","Total read-in words:",dlm.wordnum);
	fprintf(out,"%s %d\n","Total write-out words:",writenum);
	printf("%s %d\n","Total read-in words:",dlm.wordnum);
	printf("%s %d\n","Total write-out words:",writenum);
	fprintf(out,"-----------------------------------------------------\n\n");
	printf("-----------------------------------------------------\n\n");

	rewind(inp);
	readdlm(inp,&dlm,' ',0,0,'#');
	printf("------------- quotes = 0; comments = 0; -------------\n\n");
	fprintf(out,"------------- quotes = 0; comments = 0; -------------\n\n");
	writedlm(stdout,&dlm,' ');
	writenum = writedlm(out,&dlm,' ');
	fprintf(out,"%s %d\n","Total read-in words:",dlm.wordnum);
	fprintf(out,"%s %d\n","Total write-out words:",writenum);
	printf("%s %d\n","Total read-in words:",dlm.wordnum);
	printf("%s %d\n","Total write-out words:",writenum);
	fprintf(out,"-----------------------------------------------------\n\n");
	printf("-----------------------------------------------------\n\n");

	rewind(inp);
	readdlm(inp,&dlm,' ',0,0,'#');
	printf("--- quotes = 0; comments = 0; output delim = '\\t'; ---\n\n");
	fprintf(out,"--- quotes = 0; comments = 0; output delim = '\\t'; ---\n\n");
	writedlm(stdout,&dlm,'\t');
	writenum = writedlm(out,&dlm,'\t');
	fprintf(out,"%s %d\n","Total read-in words:",dlm.wordnum);
	fprintf(out,"%s %d\n","Total write-out words:",writenum);
	printf("%s %d\n","Total read-in words:",dlm.wordnum);
	printf("%s %d\n","Total write-out words:",writenum);
	fprintf(out,"-----------------------------------------------------\n");
	printf("-----------------------------------------------------\n");
	free_dlm(&dlm);

	fclose(inp);
	fclose(out);
	return 0;
}
