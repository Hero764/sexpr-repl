#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sexpr.h"
#include "names.h"
#include "tokenizer.h"
#include "operators.h"

#define MAX_NAMES 1000

static struct name names[MAX_NAMES];
static int n_names = 0;

void define_name(char *input, char *n)
{
	int rv, pos = 0;
	struct sexpr *v;
	char token_buf[20];

	if ((rv = get_token(input + pos, token_buf, 20, &pos)) < 0)
		return;

	switch (rv) {
	case TOKEN_INT:
	case TOKEN_FLOAT:
	case TOKEN_STRING:
	case TOKEN_BOOL:
		v = new_sexpr(rv, token_buf);
		break;
	case TOKEN_ATOM:
		if ((v = resolve_name(token_buf)) == NULL)
			return;
		break;
	case TOKEN_LEFTP:
		if ((rv = get_token(input + pos, token_buf, 20, &pos)) != TOKEN_ATOM) {
			printf("[ERROR] Expected atom after '('\n");
			return;
		}

		if ((v = eval_op(input + pos, token_buf, &pos)) == NULL) 
			return;
		break;
	default:
		printf("[ERROR] %s not an sexpr\n", token_buf);
		return;
	}	

	if ((rv = get_token(input + pos, token_buf, 20, &pos)) != TOKEN_RIGHTP) {
		printf("[ERROR] Expected ')' at the end of define form.\n");
		free(v);
		return;
	}

	strncpy(names[n_names].name, n, 20);
	names[n_names].expr = v;
	n_names++;
}

static struct sexpr *get_value(struct name *name)
{
	struct sexpr *v;

	if (name->expr->tag == TAG_NAME)
		v = get_value(name->expr->val.sexpr_name);
	else
		v = name->expr;

	return v;
}

struct sexpr *resolve_name(char *n)
{
	struct sexpr *result, *v;
	int i;

	for (i = 0; i < n_names; i++) {
		if (strncmp(n, names[i].name, 20) == 0)
			break;
	}

	if (i == n_names) { /* name not found */
		printf("[ERROR] Could not resolve %s\n", n);
		return NULL;
	}

	result = malloc(sizeof(struct sexpr));

	v =  get_value(&names[i]);

	result->tag = v->tag;
	result->val = v->val;

	return result;
}

void free_names()
{
	int i;

	for (i = 0; i < n_names; i++)
		free_sexpr(names[i].expr);
}
