#include "sexpr.h"

#define N_OPERATIONS 4

struct operator {
	const char *name;
	struct sexpr *(*operation_cb)(struct sexpr *operands, int n_operands);
};

struct sexpr *add_op(struct sexpr *operands, int n_operands);
struct sexpr *sub_op(struct sexpr *operands, int n_operands);
struct sexpr *mul_op(struct sexpr *operands, int n_operands);
struct sexpr *div_op(struct sexpr *operands, int n_operands);

struct operation operations[N_OPERATIONS] = {
       					   {.name = "+", .operation_cb = add_op},
					   {.name = "-", .operation_cb = sub_op},
					   {.name = "*", .operation_cb = mul_op},
					   {.name = "/", .operation_cb = div_op}
};

struct sexpr *perform_operation(

struct sexpr *add_op(struct sexpr *operands, int n_operands)
{
	int i, use_double = 0;
	int i_sum = 0;
	double d_sum;
	struct sexpr *result = malloc(sizeof(struct sexpr));

	for (i = 0; i < n_operands; i++) {
		if (operands[i].tag == TAG_FLOAT) {
			use_double = 1;
			d_sum = double(i_sum);	
		} else if ((operands[i].tag != TAG_INT) && (operands[i].tag != TAG_FLOAT)) {
			fprintf(stderr, "[ERROR] '+' takes numeric operands only.\n");
			return NULL;
		}

		use_double ? d_sum += operands[i].val->sexpr_float : i_sum += operands[i].val->sexpr_int;
	}

	if (use_double) {
		result->tag = TAG_FLOAT;
		result->val


	return result;
}
