#ifndef NAMES_H
#define NAMES_H

#include "sexpr.h"

void assign_name(char *n, struct sexpr* v);
struct sexpr *resolve_name(char *n);

#endif
