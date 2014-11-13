#include <stdio.h>
#include <stdlib.h>

#include "arithmetic.h"
#include "sexpr.h"

/* these functions are a bit messy because they have to handle integer and floating point arithmetic */

struct sexpr *add_op(struct sexpr *operands[], int n_operands)
{
	struct sexpr *result;
	int i, use_double = 0; 
	double sum = 0.0;

	if (n_operands < 2) {
		printf("[ERROR] '+' takes at least two operands\n");
		return NULL;
	}

	for (i = 0; i < n_operands; i++) {
		if (operands[i]->tag == TAG_FLOAT) {
			use_double = 1;
			sum += operands[i]->val.sexpr_float;

		} else if (operands[i]->tag == TAG_INT) {
			sum += (double) operands[i]->val.sexpr_int;

		} else {
			printf("[ERROR] '+' takes only numeric operands\n");
			return NULL;
		}
	}

	result = malloc(sizeof(struct sexpr));

	if (use_double) {
		result->tag = TAG_FLOAT;
		result->val.sexpr_float = sum;
	} else {
		result->tag = TAG_INT;
		result->val.sexpr_int = (int) sum;
	}

	return result;
}

struct sexpr *sub_op(struct sexpr *operands[], int n_operands)
{
	struct sexpr *result;
	int i, use_double = 0;
	double difference;

	if (n_operands < 1) {
		printf("[ERROR] '-' takes at least one operand\n");
		return NULL;

	} else if (n_operands < 2) { /* negation */
		if (operands[0]->tag == TAG_INT) {
			result = malloc(sizeof(struct sexpr));
			result->tag = TAG_INT;
			result->val.sexpr_int = -1 * operands[0]->val.sexpr_int;
			return result;
		} else if (operands[0]->tag == TAG_FLOAT) {
			result = malloc(sizeof(struct sexpr));
			result->tag = TAG_FLOAT;
			result->val.sexpr_float = -1 * operands[0]->val.sexpr_float;
			return result;
		} else {
			printf("[ERROR] '-' takes only numeric operands\n");
			return NULL;
		}
	}

	/* subtraction */
	if (operands[0]->tag == TAG_INT) /* difference starts out as the first operand */
		difference = (double) operands[0]->val.sexpr_int;	
	else if (operands[0]->tag == TAG_FLOAT) {
		use_double = 1;
		difference = operands[0]->val.sexpr_float;	
	} else {
		printf("[ERROR] '-' takes only numeric operands\n");
		return NULL;
	}

	for (i = 1; i < n_operands; i++) {
		if (operands[i]->tag == TAG_FLOAT) {
			use_double = 1;
			difference -= operands[i]->val.sexpr_float;

		} else if (operands[i]->tag == TAG_INT) {
			difference -= (double) operands[i]->val.sexpr_int;

		} else {
			printf("[ERROR] '+' takes only numeric operands\n");
			return NULL;
		}
	}

	result = malloc(sizeof(struct sexpr));

	if (use_double) {
		result->tag = TAG_FLOAT;
		result->val.sexpr_float = difference;
	} else {
		result->tag = TAG_INT;
		result->val.sexpr_int = (int) difference;
	}

	return result;
}

struct sexpr *mul_op(struct sexpr *operands[], int n_operands)
{
	struct sexpr *result;
	int i, use_double = 0;
	double product;

	if (n_operands < 2) {
		printf("[ERROR] '*' takes at least two operands\n");
		return NULL;
	}

	if (operands[0]->tag == TAG_INT) /* product starts out as the first operand */
		product = (double) operands[0]->val.sexpr_int;	
	else if (operands[0]->tag == TAG_FLOAT) {
		use_double = 1;
		product = operands[0]->val.sexpr_float;	
	} else {
		printf("[ERROR] '*' takes only numeric operands\n");
		return NULL;
	}

	for (i = 1; i < n_operands; i++) {
		if (operands[i]->tag == TAG_FLOAT) {
			use_double = 1;
			product *= operands[i]->val.sexpr_float;

		} else if (operands[i]->tag == TAG_INT) {
			product *= (double) operands[i]->val.sexpr_int;

		} else {
			printf("[ERROR] '*' takes only numeric operands\n");
			return NULL;
		}
	}

	result = malloc(sizeof(struct sexpr));

	if (use_double) {
		result->tag = TAG_FLOAT;
		result->val.sexpr_float = product;
	} else {
		result->tag = TAG_INT;
		result->val.sexpr_int = (int) product;
	}

	return result;
}

struct sexpr *div_op(struct sexpr *operands[], int n_operands)
{
	struct sexpr *result;
	int i, use_double = 0;
	double quotient;

	if (n_operands < 2) {
		printf("[ERROR] '/' takes at least two operands\n");
		return NULL;
	}

	if (operands[0]->tag == TAG_INT) /* quotient starts out as the first operand */
		quotient = (double) operands[0]->val.sexpr_int;	
	else if (operands[0]->tag == TAG_FLOAT) {
		use_double = 1;
		quotient = operands[0]->val.sexpr_float;	
	} else {
		printf("[ERROR] '/' takes only numeric operands\n");
		return NULL;
	}

	for (i = 1; i < n_operands; i++) {
		if (operands[i]->tag == TAG_FLOAT) {
			use_double = 1;
			quotient /= operands[i]->val.sexpr_float;

		} else if (operands[i]->tag == TAG_INT) {
			quotient /= (double) operands[i]->val.sexpr_int;

		} else {
			printf("[ERROR] '*' takes only numeric operands\n");
			return NULL;
		}
	}

	result = malloc(sizeof(struct sexpr));

	if (use_double) {
		result->tag = TAG_FLOAT;
		result->val.sexpr_float = quotient;
	} else {
		result->tag = TAG_INT;
		result->val.sexpr_int = (int) quotient;
	}

	return result;
}

struct sexpr *mod_op(struct sexpr *operands[], int n_operands)
{
	struct sexpr *result;

	if (n_operands != 2) {
		printf("[ERROR] '%%' takes exactly two operands\n");
		return NULL;
	}

	if ((operands[0]->tag != TAG_INT) || (operands[1]->tag != TAG_INT)) {
		printf("[ERROR] '%%' takes only integer operands\n");
		return NULL;
	}

	result = malloc(sizeof(struct sexpr));

	result->tag = TAG_INT;
	result->val.sexpr_int = (operands[0]->val.sexpr_int) % (operands[1]->val.sexpr_int);

	return result;
}

