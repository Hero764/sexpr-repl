#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sexpr.h"
#include "operators.h"
#include "tokenizer.h"
#include "names.h"

/* built-in operator functions */
#include "arithmetic.h"
#include "comparison.h"

#define N_OPERATIONS 11

struct operator operators[] = {
					   /* arithmetic.h */
       					   {.name = "+", .callback = add_op},
					   {.name = "-", .callback = sub_op},
					   {.name = "*", .callback = mul_op},
					   {.name = "/", .callback = div_op},
					   {.name = "%", .callback = mod_op},
					   {.name = ">", .callback = gt_op},
					   {.name = ">=", .callback = gte_op},
					   {.name = "<", .callback = lt_op},
					   {.name = "<=", .callback = lte_op},
					   {.name = "=", .callback = eq_op},
					   {.name = "!=", .callback = neq_op}
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
	struct sexpr *operand, *result;
	char token_buf[20];
	int i, rv, pos = 0;
	
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
			if ((operand = resolve_name(token_buf)) == NULL) {
				printf("[ERROR] Could not resolve: %s\n", token_buf);
				return NULL;
			}

		} else if (rv == TOKEN_LEFTP) { /* recurse */
			if ((operand = eval_op(input+pos, &pos)) == NULL)
				return NULL;
		
		} else if ((operand = new_sexpr(rv, token_buf)) == NULL) {
			printf("[ERROR] Could not create sexpr from: %s\n", token_buf);
			return NULL;
		}	
	
		/* add to operation's array of operands */
		op.operands[op.n_operands++] = operand;
	}
	
	/* evaluate */
	result = op.operator->callback(op.operands, op.n_operands);

	/* free operands */
	for (i = 0; i < op.n_operands ; i++)
		free_sexpr(op.operands[i]);
	
	if (result)
		*retpos += pos;
	
	return result;
}
