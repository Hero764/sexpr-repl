#include <stdio.h>
#include <string.h>

#include "sexpr.h"

struct sexpr *new_sexpr(int token_type, char *token_buf)
{
	struct sexpr *s = malloc(sizeof(struct sexpr));

	switch(token_type) {
	case TOKEN_INT:
		s->tag = TAG_INT;


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
