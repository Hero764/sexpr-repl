#ifndef OPERATORS_H
#define OPERATORS_H

#define MAX_OPERANDS 10

struct operator {
	const char *name;
	struct sexpr *(*callback)(struct sexpr *operands[], int n_operands);
};

struct operation {
	struct operator *operator;
	int n_operands;
	struct sexpr *operands[MAX_OPERANDS];
};

struct sexpr *eval_op(char *input, int *pos);

#endif
