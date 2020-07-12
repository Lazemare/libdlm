typedef struct DLM {
	/* Total line number */
	int linenum;
	/* Word number per line */
	int *wordnum;
	/* Main array */
	char ***list;
} dlm_t;

void free_dlm(dlm_t *dlm);
void readdlm(FILE *fp, dlm_t *dlm, char delim, int quotes, \
	int comments, char comment_char);
int writedlm(FILE *fp, dlm_t *dlm, char delim);
