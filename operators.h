#ifndef OPERATORS_H
#define OPERATORS_H

#define MAX_OPERANDS 10

struct operator {
	const char *name;
	struct sexpr *(*operation_cb)(struct sexpr *operands, int n_operands);
};

struct operation {
	struct operator *operator;
	int n_operands;
	struct sexpr operands[MAX_OPERANDS];
};

int eval_op(char *input, char *output, int n, int *pos);

#endif
