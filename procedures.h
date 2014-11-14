#ifndef CODE_H
#define CODE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_ARGS 10
#define MAX_CODESZ 1024 

struct procedure {
	char name[20];
	int n_args;
	char procedure_str[MAX_CODESZ];
};

struct procedure *get_procedure(char *n);
char *get_procedure_string(struct procedure *c, int argc, char **args);
void define_procedure(char *input);

#endif
