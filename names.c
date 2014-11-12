#include <string.h>

#include "sexpr.h"
#include "names.h"

#define MAX_NAMES 1000

static struct name names[MAX_NAMES];
static int n_names = 0;

void assign_name(char *n, struct sexpr *v)
{
	int i;

	for (i = 0; i < MAX_NAMES; i++) {
		if (strncmp(n, names[i].name, 20) == 0) {
			names[i].expr = v;
			return;
		}
	}

	/* first time name is being used */
	strncpy(names[n_names].name, n, 20);
	names[n_names++].expr = v;
}

static struct sexpr *get_value(struct name *name)
{
	struct sexpr *result;

	if (name->expr->tag == TAG_NAME)
		result = get_value(name->expr->val.sexpr_name);
	else
		result = name->expr;

	return result;
}

struct sexpr *resolve_name(char *n)
{
	int i;

	for (i = 0; i < n_names; i++) {
		if (strncmp(n, names[i].name, 20) == 0)
			break;
	}

	if (i == n_names) /* name not found */
		return NULL;	

	return get_value(&names[i]);
}	
