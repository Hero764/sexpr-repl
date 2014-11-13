#ifndef SEXPR_H
#define SEXPR_H

#define TAG_INT    1
#define TAG_FLOAT  2
#define TAG_NAME   3
#define TAG_STRING 4

union value {
	long   sexpr_int;
	double sexpr_float;
	struct name *sexpr_name;
	char *sexpr_string;
};

struct sexpr {
	int tag;
	union value val;
};

struct name {
	char name[20];
	struct sexpr *expr;
};

int get_string(struct sexpr *s, char *buf, int n);
struct sexpr *new_sexpr(int token_type, char *token_buf);
void free_sexpr(struct sexpr *s);

#endif
