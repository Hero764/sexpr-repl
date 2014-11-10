#include <stdio.h>

#include "sexpr.h"
#include "tokenizer.h"

int repr(struct sexpr *s, char *buf, int n)
{
	switch (s->tag) {
		case TAG_INT:
			snprintf(buf, n, "%d", s->val.sexpr_int);
			break;
		case TAG_FLOAT:
			snprintf(buf, n, "%f", s->val.sexpr_float);
			break;
		case TAG_STRING:
			strncpy(buf, s->val.sexpr_string, n);
			break;
		default:
			return -1;
	}
	
	return 0;
}

char *evaluate(char *line) 
{
	struct operation op;
	char token_buf[100];
}

int main (int argc, char **argv)
{
	char line[1024], result[1024];

	while (fgets(line, 1024, stdin) != NULL)
		printf("%s\n", evaluate(line, result);

	return 0;
}
