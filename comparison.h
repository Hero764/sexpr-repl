#ifndef COMPARISON_H
#define COMPARISON_H

struct sexpr *gt_op(struct sexpr *operands[], int n_operands);
struct sexpr *gte_op(struct sexpr *operands[], int n_operands);
struct sexpr *lt_op(struct sexpr *operands[], int n_operands);
struct sexpr *lte_op(struct sexpr *operands[], int n_operands);
struct sexpr *eq_op(struct sexpr *operands[], int n_operands);
struct sexpr *neq_op(struct sexpr *operands[], int n_operands);

#endif
