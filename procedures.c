#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "procedures.h"
#include "tokenizer.h"

#define MAX_PROCEDURES 1000

struct procedure procedures[MAX_PROCEDURES];
static int n_procedures = 0;

static int arg_match(char *str, int argc, char **args) {
	int i;

	for (i = 0; i < argc; i++) {
		if (strncmp(args[i], str, 20) == 0)
			return i;
	}

	return -1;
}

void define_procedure(char *input)
{
	char code[MAX_CODESZ], token_buf[20], arg_rep[3];
	char args[MAX_ARGS][20];
	int pos = 0, p_state = 1, rv;
	int argc, argn;

	/* get proecedure name */
	if ((rv = get_token(input + pos, token_buf, 20, &pos)) != TOKEN_ATOM) {
	       printf("[ERROR] Expected atom after '('\n");
	       return;
	}

	strncpy(procedures[n_procedures].name, token_buf, 20);

	while ((rv = get_token(input + pos, token_buf, 20, &pos)) != TOKEN_RIGHTP) {
		if (rv != TOKEN_ATOM) {
			printf("[ERROR] Expected atom as formal argument\n");
			return;
		}

		strncpy(args[argc], token_buf, 20);
		argc++;

		if (argc >= MAX_ARGS) {
			printf("[ERROR] Fuck you that's way too many arguments!\n");
			return;
		}
	}

	if ((rv = get_token(input + pos, token_buf, 20, &pos)) != TOKEN_LEFTP) {
		printf("[ERROR] Expected '(' as beginning of procedure.\n");
		return;
	}

	code[0] = '\0';
	
	while (p_state != 0) {
		rv = get_token(input + pos, token_buf, 20, &pos);
		if (rv == TOKEN_ATOM) {
			argn = arg_match(token_buf, argc, args);
			if (argn < 0)
				strncat(code, token_buf, 20);
			else {
				snprintf(arg_rep, 3, "$%d", argn); 
				strncat(code, arg_rep, 3);
			}
		} else if (rv == TOKEN_LEFTP) {
			p_state++;
			strncat(code, token_buf, 2);
		} else if (rv == TOKEN_RIGHTP) {
			p_state--;
			strncat(code, token_buf, 2);
		} else
			strncat(code, token_buf, 20);

		strncat(code, " ", 2);
	}

	if ((rv = get_token(input + pos, token_buf, 20, &pos)) != TOKEN_RIGHTP) {
		printf("[ERROR] Expect ')' at end of define form\n");
		return;
	}

	procedures[n_procedures].n_args = argc;
	strncpy(procedures[n_procedures].procedure_str, code, MAX_CODESZ);
	n_procedures++;
}

struct procedure *get_procedure(char *n)
{
	int i;
	
	for (i = 0; i < n_procedures; i++) {
		if (strncmp(procedures[i].name, n, 20) == 0)
			return &procedures[i];
	}

	return NULL;
}

char *get_procedure_string(struct procedure *p, int argc, char **args)
{
	char new_str[MAX_CODESZ * 2], *return_string;
	int argn;

	int i, j, k = 0;

	if (argc != p->n_args) {
		printf("[ERROR] %s takes exactly %d arguments.\n", p->name, p->n_args);
		return NULL;
	}

	for (i = 0; p->procedure_str[i] != '\0'; i++) {
		if (p->procedure_str[i] == '$') {
			i++;
			argn = p->procedure_str[i] - '0'; 
			if (argn >= argc) {
				printf("[ERROR] Invalid argument number\n");
				return NULL;
			}

			j = 0;
			while (args[argn][j] != '\0')
				new_str[k++] = args[argn][j++];
		
		} else
			new_str[k++] = p->procedure_str[i++];
	}

	new_str[k] = '\0';
	return_string = malloc(k);
	strncpy(return_string, new_str, k);

	return return_string;
}
