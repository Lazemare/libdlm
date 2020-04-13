/* Max line number. */
#define MAXLINES 50
/* Max word number per line. */
#define MAXWORDS 100
/* Max letter number per word. */
#define MAXLETTERS 100
/* End of line */
#define EOL '\n'

int readdlm(FILE *fp, char list[MAXLINES][MAXWORDS][MAXLETTERS], \
	char delim,int quotes, int comments, char comment_char);
int writedlm(FILE *fp, char list[MAXLINES][MAXWORDS][MAXLETTERS], char delim);
