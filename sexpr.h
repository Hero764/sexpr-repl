#ifndef SEXPR_H
#define SEXPR_H

#define TAG_INT    1
#define TAG_FLOAT  2
#define TAG_NAME   3
#define TAG_STRING 4
#define TAG_BOOL   5

#define MAX_REPR 100

union value {
	long sexpr_int;
	double sexpr_float;
	struct name *sexpr_name;
	char *sexpr_string;
	int sexpr_bool;
};

struct sexpr {
	int tag;
	union value val;
};

int get_string(struct sexpr *s, char *buf, int n);
struct sexpr *new_sexpr(int token_type, char *token_buf);
void free_sexpr(struct sexpr *s);

#endif
