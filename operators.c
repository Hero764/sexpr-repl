#include <stdio.h>
#include <stdlib.h>

#include "sexpr.h"
#include "operators.h"
#include "tokenizer.h"


#define N_OPERATIONS 4

struct sexpr *add_op(struct sexpr *operands, int n_operands);
struct sexpr *sub_op(struct sexpr *operands, int n_operands);
struct sexpr *mul_op(struct sexpr *operands, int n_operands);
struct sexpr *div_op(struct sexpr *operands, int n_operands);

struct operator operators[] = {
       					   {.name = "+", .operation_cb = add_op},
					   {.name = "-", .operation_cb = NULL},
					   {.name = "*", .operation_cb = NULL},
					   {.name = "/", .operation_cb = NULL}
};

struct operator *get_op(char *op_name)
{
	int i;

	for (i = 0; i < N_OPERATIONS; i++) {
		if (strncmp(operators[i].name, op_name, 20) == 0)
			return &operators[i];
	}

	return NULL;
}	

struct sexpr *eval_op(char *input, int *retpos)
{
	struct operation op;
	struct sexpr *operand;
	char token_buf[20];
	int rv, pos = 0;
	
	op.n_operands = 0;

	/* get operator */
	rv = get_token(input + pos, token_buf, 20, &pos);
	if (rv != TOKEN_ATOM) {
		printf("[ERROR] Expected operator after left parenthesis.\n");
		return NULL;
	}

	if ((op.operator = get_op(token_buf)) == NULL) {
		printf("[ERROR] %s not an operator\n", token_buf);
		return NULL;
	}

	/* get operands */
	while ((rv = get_token(input + pos, token_buf, 20, &pos)) != TOKEN_RIGHTP) {
		if (op.n_operands == MAX_OPERANDS) {
			printf("[ERROR] Too many operands for an expression.\n");
			return NULL;
		}	
		
		if (rv == TOKEN_ATOM) {
			if ((operand = resolve_name(token_buf)) = NULL) {
				printf("[ERROR] Could not resolve: %s\n", token_buf);
				return NULL;
			}

		} else if (rv == TOKEN_LEFTP) { /* recurse */
			if ((operand = eval_op(input+pos, &pos)) == NULL)
				return NULL;
		
		} else if ((operand = new_sexpr(rv, token_buf)) = NULL) {
			printf("[ERROR] Could not create sexpr from: %s\n", token_buf);
			return NULL;
		}
		
		/* add to operation's array of operands */
		op.operands[n_operands++] = operand;	
	}
	
	/* evaluate */
	return perform_operation(op);
}

struct sexpr *add_op(struct sexpr *operands, int n_operands)
{
	int i, use_double = 0;
	int i_sum = 0;
	double d_sum;
	struct sexpr *result = malloc(sizeof(struct sexpr));

	for (i = 0; i < n_operands; i++) {
		if (operands[i].tag == TAG_FLOAT) {
			use_double = 1;
			d_sum = (double) i_sum;

		} else if ((operands[i].tag != TAG_INT) && (operands[i].tag != TAG_FLOAT)) {
			fprintf(stderr, "[ERROR] '+' takes numeric operands only.\n");
			return NULL;
		}

	}

	return result;
}
