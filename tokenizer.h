#ifndef TOKENIZER_H
#define TOKENIZER_H

#define TOKEN_INT    1
#define TOKEN_FLOAT  2
#define TOKEN_ATOM   3
#define TOKEN_STRING 4
#define TOKEN_LEFTP  5
#define TOKEN_RIGHTP 6
#define TOKEN_LEFTB  7
#define TOKEN_RIGHTB 8
#define TOKEN_DOT    9

int tokenize(char *input, char *token, int n);

#endif
