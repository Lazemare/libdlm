/* Max line number. */
#define MAXLINES 200
/* Max word number per line. */
#define MAXWORDS 50
/* Max letter number per word. */
#define MAXLETTERS 50
/* End of line */
#define EOL '\n'

struct DLM {
	/* Line number */
	int linenum;
	/* Word number */
	int wordnum;
	/* Main array */
	char ***list;
};

void init_dlm(struct DLM *dlm);
void free_dlm(struct DLM *dlm);
void readdlm(FILE *fp, struct DLM *dlm, char delim, int quotes, \
	int comments, char comment_char);
int writedlm(FILE *fp, struct DLM *dlm, char delim);
