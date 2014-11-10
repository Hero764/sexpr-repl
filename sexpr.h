#ifndef SEXPR_H
#define SEXPR_H

#define TAG_INT    1
#define TAG_FLOAT  2
#define TAG_ATOM   3
#define TAG_STRING 4

struct atom {
	const char *name;
	union value* val;
};

union value {
	long   sexpr_int;
	double sexpr_float;
	struct atom sexpr_atom;
	char *sexpr_string;
};

struct sexpr {
	int tag;
	union value *val;
};

#endif
