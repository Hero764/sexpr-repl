#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sexpr.h"
#include "tokenizer.h"

struct sexpr *new_sexpr(int token_type, char *token_buf)
{
	struct sexpr *s = malloc(sizeof(struct sexpr));

	switch(token_type) {
	case TOKEN_INT:
		s->tag = TAG_INT;
		s->val.sexpr_int = atol(token_buf);
		break;
	case TOKEN_FLOAT:
		s->tag = TAG_FLOAT;
		s->val.sexpr_float = atof(token_buf);
		break;
	case TOKEN_STRING:
		s->tag = TAG_STRING;
		s->val.sexpr_string = malloc(100);
		strncpy(s->val.sexpr_string, token_buf, 100);
		break;
	}

	return s;
}

int get_string(struct sexpr *s, char *buf, int n)
{
	switch (s->tag) {
		case TAG_INT:
			snprintf(buf, n, "%ld", s->val.sexpr_int);
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

void free_sexpr(struct sexpr *s)
{
	if (s->tag == TAG_STRING)
		free(s->val.sexpr_string);
	free(s);
}
