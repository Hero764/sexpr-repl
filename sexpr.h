#ifndef SEXPR_H
#define SEXPR_H

#define TAG_INT    1
#define TAG_FLOAT  2
#define TAG_NAME   3
#define TAG_STRING 4

struct name {
	char name[20];
	struct sexpr *expr;
};

union value {
	long   sexpr_int;
	double sexpr_float;
	struct name *sexpr_name;
	char *sexpr_string;
};

struct sexpr {
	int tag;
	union value value;
};

#endif
