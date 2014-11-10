#ifndef NAMES_H
#define NAMES_H

#include "sexpr.h"

int assign_name(struct name n, struct sexpr* v);
struct sexpr *resolve_name(struct name n);

#endif
