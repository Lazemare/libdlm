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
	int i,j;
	int in,put;
	int flag;
	char list[MAXLINES][MAXWORDS][MAXLETTERS];

	memset(list, 0, sizeof list);
	in = readdlm(inp,list,' ',0,0,'#');
	printf("quotes = 0; comments = 0; comment_char='#':\n");
	fprintf(out,"quotes = 0; comments = 0; comment_char='#':\n");
	writedlm(stdout,list,' ');
	put = writedlm(out,list,' ');
	fprintf(out,"%s %d\n","Total read-in words:",in);
	fprintf(out,"%s %d\n","Total write-out words:",put);
	printf("%s %d\n","Total read-in words:",in);
	printf("%s %d\n","Total write-out words:",put);
	fprintf(out,"\n");
	printf("\n");

	rewind(inp);
	memset(list, 0, sizeof list);
	in = readdlm(inp,list,' ',1,0,'#');
	printf("quotes = 1; comments = 0; comment_char='#':\n");
	fprintf(out,"quotes = 1; comments = 0; comment_char='#':\n");
	writedlm(stdout,list,' ');
	put = writedlm(out,list,' ');
	fprintf(out,"%s %d\n","Total read-in words:",in);
	fprintf(out,"%s %d\n","Total write-out words:",put);
	printf("%s %d\n","Total read-in words:",in);
	printf("%s %d\n","Total write-out words:",put);
	fprintf(out,"\n");
	printf("\n");

	rewind(inp);
	memset(list, 0, sizeof list);
	in = readdlm(inp,list,' ',1,1,'#');
	printf("quotes = 1; comments = 1:\n");
	fprintf(out,"quotes = 1; comments = 1:\n");
	writedlm(stdout,list,' ');
	put = writedlm(out,list,' ');
	fprintf(out,"%s %d\n","Total read-in words:",in);
	fprintf(out,"%s %d\n","Total write-out words:",put);
	printf("%s %d\n","Total read-in words:",in);
	printf("%s %d\n","Total write-out words:",put);
	fprintf(out,"\n");
	printf("\n");

	rewind(inp);
	memset(list, 0, sizeof list);
	in = readdlm(inp,list,' ',1,1,'#');
	printf("quotes = 1; comments = 1; output delim = '\\t':\n");
	fprintf(out,"quotes = 1; comments = 1; output delim = '\\t':\n");
	writedlm(stdout,list,'\t');
	put = writedlm(out,list,'\t');
	fprintf(out,"%s %d\n","Total read-in words:",in);
	fprintf(out,"%s %d\n","Total write-out words:",put);
	printf("%s %d\n","Total read-in words:",in);
	printf("%s %d\n","Total write-out words:",put);
	fprintf(out,"\n");
	printf("\n");

	fclose(inp);
	fclose(out);
	return 0;
}

