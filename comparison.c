#include <stdio.h>
#include <stdlib.h>

#include "comparison.h"
#include "sexpr.h"

struct sexpr *gt_op(struct sexpr *operands[], int n_operands)
{
	struct sexpr *result;
	double vals[2];
	int i;

	if (n_operands != 2) {
		printf("[ERROR] '>' takes exactly two operands\n");
		return NULL;
	}

	for (i = 0; i < 2; i++) {
		if (operands[i]->tag == TAG_INT)
			vals[i] = (double) operands[i]->val.sexpr_int;
		else if (operands[i]->tag == TAG_FLOAT)
			vals[i] = operands[i]->val.sexpr_float;
		else {
			printf("[ERROR] '>' takes only numeric arguments.\n");
			return NULL;
		}
	}

	result = malloc(sizeof(struct sexpr));

	result->tag = TAG_BOOL;
	result->val.sexpr_bool = (vals[0] > vals[1]);

	return result;
}

struct sexpr *gte_op(struct sexpr *operands[], int n_operands)
{
	struct sexpr *result;
	double vals[2];
	int i;

	if (n_operands != 2) {
		printf("[ERROR] '>=' takes exactly two operands\n");
		return NULL;
	}

	for (i = 0; i < 2; i++) {
		if (operands[i]->tag == TAG_INT)
			vals[i] = (double) operands[i]->val.sexpr_int;
		else if (operands[i]->tag == TAG_FLOAT)
			vals[i] = operands[i]->val.sexpr_float;
		else {
			printf("[ERROR] '>=' takes only numeric arguments.\n");
			return NULL;
		}
	}

	result = malloc(sizeof(struct sexpr));

	result->tag = TAG_BOOL;
	result->val.sexpr_bool = (vals[0] >= vals[1]);

	return result;
}

struct sexpr *lt_op(struct sexpr *operands[], int n_operands)
{
	struct sexpr *result;
	double vals[2];
	int i;

	if (n_operands != 2) {
		printf("[ERROR] '<' takes exactly two operands\n");
		return NULL;
	}

	for (i = 0; i < 2; i++) {
		if (operands[i]->tag == TAG_INT)
			vals[i] = (double) operands[i]->val.sexpr_int;
		else if (operands[i]->tag == TAG_FLOAT)
			vals[i] = operands[i]->val.sexpr_float;
		else {
			printf("[ERROR] '<' takes only numeric arguments.\n");
			return NULL;
		}
	}

	result = malloc(sizeof(struct sexpr));

	result->tag = TAG_BOOL;
	result->val.sexpr_bool = (vals[0] < vals[1]);

	return result;
}

struct sexpr *lte_op(struct sexpr *operands[], int n_operands)
{
	struct sexpr *result;
	double vals[2];
	int i;

	if (n_operands != 2) {
		printf("[ERROR] '<=' takes exactly two operands\n");
		return NULL;
	}

	for (i = 0; i < 2; i++) {
		if (operands[i]->tag == TAG_INT)
			vals[i] = (double) operands[i]->val.sexpr_int;
		else if (operands[i]->tag == TAG_FLOAT)
			vals[i] = operands[i]->val.sexpr_float;
		else {
			printf("[ERROR] '<=' takes only numeric arguments.\n");
			return NULL;
		}
	}

	result = malloc(sizeof(struct sexpr));

	result->tag = TAG_BOOL;
	result->val.sexpr_bool = (vals[0] <= vals[1]);

	return result;
}

struct sexpr *eq_op(struct sexpr *operands[], int n_operands)
{
	struct sexpr *result;
	double vals[2];
	int i;

	if (n_operands != 2) {
		printf("[ERROR] '=' takes exactly two operands\n");
		return NULL;
	}

	for (i = 0; i < 2; i++) {
		if (operands[i]->tag == TAG_INT)
			vals[i] = (double) operands[i]->val.sexpr_int;
		else if (operands[i]->tag == TAG_FLOAT)
			vals[i] = operands[i]->val.sexpr_float;
		else {
			printf("[ERROR] '=' takes only numeric arguments.\n");
			return NULL;
		}
	}

	result = malloc(sizeof(struct sexpr));

	result->tag = TAG_BOOL;
	result->val.sexpr_bool = (vals[0] == vals[1]);

	return result;
}

struct sexpr *neq_op(struct sexpr *operands[], int n_operands)
{
	struct sexpr *result;
	double vals[2];
	int i;

	if (n_operands != 2) {
		printf("[ERROR] '!=' takes exactly two operands\n");
		return NULL;
	}

	for (i = 0; i < 2; i++) {
		if (operands[i]->tag == TAG_INT)
			vals[i] = (double) operands[i]->val.sexpr_int;
		else if (operands[i]->tag == TAG_FLOAT)
			vals[i] = operands[i]->val.sexpr_float;
		else {
			printf("[ERROR] '!=' takes only numeric arguments.\n");
			return NULL;
		}
	}

	result = malloc(sizeof(struct sexpr));

	result->tag = TAG_BOOL;
	result->val.sexpr_bool = (vals[0] != vals[1]);

	return result;
}
