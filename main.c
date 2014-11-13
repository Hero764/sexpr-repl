#include <stdio.h>
#include <string.h>

#include "sexpr.h"
#include "operators.h"
#include "tokenizer.h"
#include "names.h"

int count_parenthesis(char *line, int p_state)
{
	int i;

	for (i = 0; line[i] != '\0'; i++) {
		if (line[i] == '(') 
			p_state++;
		else if (line[i] == ')') {
			if (p_state == 0)
				return -1; /* right parenthesis with no left parenthesis to close */
			p_state--;
		}
	}

	return p_state;
}

void skip_op(char *op, int *retpos)
{
	int i = 0;
	int p_state = 1;

	while (p_state > 0) {
		if (op[i] == ')')
			p_state--;
		else if (op[i] == '(')
			p_state++;
		i++;
	}

	*retpos += i;
}

void print_result(char *input) 
{
	struct sexpr *s;
	char token_buf[100], repr_buf[100];
	int pos, rv;

	pos = 0;

	while ((rv = get_token(input + pos, token_buf, 100, &pos)) > 0) {
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
			
			if (get_string(s, repr_buf, 100) < 0)
				break;

			printf("%s\n", repr_buf);
			break;

		case TOKEN_LEFTP:
			if ((s = eval_op(input + pos, &pos)) == NULL) {
				skip_op(input + pos, &pos);
				break;
			}

			if (get_string(s, repr_buf, 100) < 0)
				break;


			free_sexpr(s);

			printf("%s\n", repr_buf);
			break;

		default:
			printf("Unspecified error.\n");
		}
	}
}

int main(int argc, char **argv)
{
	char line[1024], input[8096];
	int p_state = 0;
	
	printf("Welcome to Hero's REPL v 0.1\n");
	printf(">> ");

	while (fgets(line, 1024, stdin) != NULL) {
		p_state = count_parenthesis(line, p_state);

		if (p_state == 0) { /* all parenthesis closed, concatenate and evaluate */
			strncat(input, line, 1024);
			print_result(input);

			p_state = 0;
			input[0] = '\0';
			printf(">> ");

		} else if (p_state < 0) { /* you fucked up */
			printf("[ERROR] Mismatched parenthesis\n");

			p_state = 0;
			input[0] = '\0';
			printf(">> ");

		} else /* still waiting to close some parenthesis, */
			strncat(input, line, 1024);

	}

	putchar('\n');
	free_names();
	return 0;
}
