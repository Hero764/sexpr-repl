/* tokenizer.c
 * 
 * This module provides functions for retrieving tokens from input.
 *
 * Written by Tyler Jarjoura
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "tokenizer.h"

#define is_illegal(c) ((c == '(') || (c == ')') || (c == '[') || (c == ']') || (c == '.') || (c == '\"'))
#define is_term(c) ((c == ' ') || (c == '\n') || (c == '\t') || (c == ')') || (c == ']'))

static int get_number(char *bufp, char *token_buf, int n, int *number_type)
{
	int type = TOKEN_INT, len = 0;
	int exponent = 0, number = 0;

	while (!is_term(*bufp)) {
		if (*bufp == '.') {
			if (exponent) {
				fprintf(stderr, "[ERROR] only integer exponents allowed\n");
				return -1;
			}

			type = TOKEN_FLOAT;
		
		} else if ((*bufp == 'e') || (*bufp == 'E')) {
			if (!number) {
				fprintf(stderr, "[ERROR] expected digit before exponent\n");
				return -1;
			}

			type = TOKEN_FLOAT;
		
		} else if (isdigit(*bufp))
			number = 1;

		len++;
		if (len > n) {
			fprintf(stderr, "[ERROR] token buffer too small\n");
			return -1;
		}	
		
		*token_buf++ = *bufp++;
	}

	*token_buf = '\0';	

	*number_type = type;
	return len;
}

static int get_atom(char *bufp, char *token_buf, int n)
{
	int len = 0;

	while (!is_term(*bufp)) {
		if (is_illegal(*bufp)) {
			fprintf(stderr, "[ERROR] illegal character detected in atom\n");
			return -1;
		}
	
		len++;
		if (len > n) {
			fprintf(stderr, "[ERROR] token buffer too small\n");
			return -1;
		}

		*token_buf++ = *bufp++;
	}

	*token_buf = '\0';
	return len;
}

static int get_string(char *bufp, char *token_buf, int n)
{
	int len = 0;

	*token_buf++ = *bufp++; //copy intial initial '"'
	len++;

	while (*bufp != '\"') {
		if (*bufp == '\0') {
			fprintf(stderr, "[ERROR] expected terminating \" \n");
			return -1;
		}

		len++;
		if (len > n) {
			fprintf(stderr, "[ERROR] token buffer too small\n");
			return -1;
		}

		*token_buf++ = *bufp++;
	}

	*token_buf++ = *bufp++; //copy terminating '"'
	len ++; // for the two '"'s

	*token_buf = '\0';
	return len;
}	

/* Returns an integer corresponding to the type of token retrieved, 0 when there is no more input, or -1 on error */

int get_token(char *buffer, char *token_buf, int n, int *retpos)
{
	int pos = 0;

	int rv, number_type;

	while (isspace(buffer[pos])) pos++;

	if (buffer[pos] == '\0') 
		return 0;
	
	if ((buffer[pos] == '+') || (buffer[pos] == '-')) { /* number with sign prefix or atom */
		if ((buffer[pos+1] == '.') || (isdigit(buffer[pos+1]))) {
			if ((rv = get_number(&buffer[pos], token_buf, n, &number_type)) < 0)
			       return -1;	
			pos += rv;
			*retpos += pos;
			return number_type;

		} else {
			if ((rv = get_atom(&buffer[pos], token_buf, n)) < 0)
				return -1;
			pos += rv;
			*retpos += pos;
			return TOKEN_ATOM;
		}

	} else if (isdigit(buffer[pos])) { /* number */
		if ((rv = get_number(&buffer[pos], token_buf, n, &number_type)) < 0)
			return -1;
		pos += rv;
		*retpos += pos;
		return number_type;
		
	} else if (buffer[pos] == '\"') { /* string */
		if ((rv = get_string(&buffer[pos], token_buf, n)) < 0)
			return -1;
		pos += rv;
		*retpos += pos;
		return TOKEN_STRING;

	} else if (buffer[pos] == '#') { /* truth value */
		if (buffer[pos+1] == 't') {
			token_buf[0] = '#';
			token_buf[1] = 't';
			token_buf[2] = '\0';

		} else if (buffer[pos+1] == 'f') {
			token_buf[0] = '#';
			token_buf[1] = 't';
			token_buf[2] = '\0';
		} else {
			printf("[ERROR] expected 't' or 'f' after '#'\n");
			return -1;
		}
		
		pos += 2;
		*retpos += pos;
		return TOKEN_BOOL;

	} else if (buffer[pos] == '.') { /* floating point or dot token  */
		if (isdigit(buffer[pos+1])) {
			if ((rv = get_number(&buffer[pos], token_buf, n, &number_type)) < 0)
				return -1;
			pos += rv;
			*retpos += pos;
			return number_type;
		}
	
		pos++;
		*retpos += pos;
		return TOKEN_DOT;

	} else if (buffer[pos] == '(') { /* left parenthesis */
		token_buf[0] = '(';
		token_buf[1] = '\0';
		pos++;
		*retpos += pos;
		return TOKEN_LEFTP;
	
	} else if (buffer[pos] == ')') { /* right parenthesis */
		token_buf[0] = ')';
		token_buf[1] = '\0';
		pos++;
		*retpos += pos;
		return TOKEN_RIGHTP;
	
	} else if (buffer[pos] == '[') { /* left bracket */
		token_buf[0] = '[';
		token_buf[1] = '\0';
		pos++;
		*retpos += pos;
		return TOKEN_LEFTB;
	
	} else if (buffer[pos] == ']') { /* right bracket */
		token_buf[0] = ']';
		token_buf[1] = '\0';
		pos++;
		*retpos += pos;
		return TOKEN_RIGHTB;

	} else { /* name */
		if ((rv = get_atom(&buffer[pos], token_buf, n)) < 0)
			return -1;
		pos += rv;
		*retpos += pos;
		return TOKEN_ATOM;
	}
}		
