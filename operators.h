#ifndef OPERATORS_H
#define OPERATORS_H

#define MAX_OPERANDS 10

struct operation {
	char op_name[20];
	struct sexpr operands[MAX_OPERANDS];
};

#endif
