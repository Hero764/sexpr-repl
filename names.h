#ifndef NAMES_H
#define NAMES_H

#include "sexpr.h"

struct name {
	char name[20];
	struct sexpr *expr;
};

void define_name(char *input, char *n);
struct sexpr *resolve_name(char *n);
void free_names();

#endif
