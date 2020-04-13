#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delimitedfile.h"

int main(void)
{
	FILE *inp;
	FILE *out;
	inp = fopen("txt","r");
	out = fopen("out","w");
	int i,j;
	int flag;
	char list[MAXLINES][MAXWORDS][MAXLETTERS];

	memset(list, 0, sizeof list);
	readdlm(inp,list,' ',0,0,'#');
	printf("quotes = 0; comments = 0; comment_char='#':\n");
	fprintf(out,"quotes = 0; comments = 0; comment_char='#':\n");
	writedlm(stdout,list,' ');
	writedlm(out,list,' ');
	fprintf(out,"\n");
	printf("\n");

	rewind(inp);
	memset(list, 0, sizeof list);
	readdlm(inp,list,' ',1,0,'#');
	printf("quotes = 1; comments = 0; comment_char='#':\n");
	fprintf(out,"quotes = 1; comments = 0; comment_char='#':\n");
	writedlm(stdout,list,' ');
	writedlm(out,list,' ');
	fprintf(out,"\n");
	printf("\n");

	rewind(inp);
	memset(list, 0, sizeof list);
	readdlm(inp,list,' ',1,1,'#');
	printf("quotes = 1; comments = 1:\n");
	fprintf(out,"quotes = 1; comments = 1:\n");
	writedlm(stdout,list,' ');
	writedlm(out,list,' ');
	fprintf(out,"\n");
	printf("\n");

	rewind(inp);
	memset(list, 0, sizeof list);
	readdlm(inp,list,' ',1,1,'#');
	printf("quotes = 1; comments = 1; output delim = '\\t':\n");
	fprintf(out,"quotes = 1; comments = 1; output delim = '\\t':\n");
	writedlm(stdout,list,'\t');
	writedlm(out,list,'\t');
	fprintf(out,"\n");
	printf("\n");

	fclose(inp);
	fclose(out);
	return 0;
}

