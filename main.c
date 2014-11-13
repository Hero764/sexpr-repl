#include <stdio.h>
#include <string.h>

#include "sexpr.h"
#include "operators.h"
#include "tokenizer.h"
#include "names.h"

void print_result(char *line) 
{
	struct sexpr *s;
	char token_buf[100], repr_buf[100];
	int pos, rv;

	pos = 0;

	while ((rv = get_token(line + pos, token_buf, 100, &pos)) > 0) {
		switch (rv) {
		case TOKEN_INT:
		case TOKEN_FLOAT:
		case TOKEN_STRING:
			printf("%s\n", token_buf);
			break;

		case TOKEN_ATOM:
			if ((s = resolve_name(token_buf)) == NULL) {
				printf("Error resolving name: %s\n", token_buf);
				break;
			}
			
			if (get_string(s, repr_buf, 100) < 0) {
				printf("Error reading sexpr tag\n");
				break;
			}

			printf("%s\n", repr_buf);
			break;

		case TOKEN_LEFTP:
			if ((s = eval_op(line + pos, &pos)) == NULL) {
				printf("Error evaluating operation\n");
				break;
			}

			if (get_string(s, repr_buf, 100) < 0) {
				printf("Error reading sexpr tag\n");
				break;
			}

			printf("%s\n", repr_buf);
			break;

		default:
			printf("Unspecified error.\n");
		}
	}
}

int main(int argc, char **argv)
{
	char line[1024];

	printf("Welcome to Hero's REPL v 0.1\n");
	printf(">> ");

	while (fgets(line, 1024, stdin) != NULL) {
		print_result(line);
		printf(">> ");
	}

	putchar('\n');	
	free_names();
	return 0;
}
