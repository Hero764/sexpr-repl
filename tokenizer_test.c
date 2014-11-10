#include <stdio.h>

#include "tokenizer.h"

int main(int argc, char **argv)
{
	char line[100];
	char token[100];
	int input_set, eol, rv;

	while (fgets(line, 100, stdin) != NULL) {
		input_set = 0;
		eol = 0;
		while (!eol) {
			if (!input_set) {
				rv = tokenize(line, token, 100);
				input_set = 1;
			} else 
				rv = tokenize(NULL, token, 100);
		
			if (rv < 0)
				break;

			switch (rv) {
				case 0:
					eol = 1;
					break;
				case TOKEN_INT:
					printf("Integer: %s\n", token);	
					break;
				case TOKEN_FLOAT:
					printf("Floating point: %s\n", token);
					break;
				case TOKEN_ATOM:
					printf("Atom: %s\n", token);
				     	break;
				case TOKEN_STRING:
					printf("String: %s\n", token);
					break;
				case TOKEN_LEFTP:
					printf("Left parenthesis: %s\n", token);
					break;
				case TOKEN_RIGHTP:
					printf("Right parenthesis: %s\n", token);
					break;
				case TOKEN_LEFTB:
					printf("Left bracket: %s\n", token);
					break;
				case TOKEN_RIGHTB:
					printf("Right bracket: %s\n", token);
					break;
				case TOKEN_DOT:
					printf("Dot: %s\n", token);
					break;
			}
		}
	}

	return 0;
}
