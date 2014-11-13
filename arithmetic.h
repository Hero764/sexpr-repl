#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "sexpr.h"

struct sexpr *add_op(struct sexpr *operands[], int n_operands);
struct sexpr *sub_op(struct sexpr *operands[], int n_operands);
struct sexpr *mul_op(struct sexpr *operands[], int n_operands);
struct sexpr *div_op(struct sexpr *operands[], int n_operands);
struct sexpr *mod_op(struct sexpr *operands[], int n_operands);

#endif
