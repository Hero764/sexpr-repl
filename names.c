#include "sexpr.h"
#include "names.h"

#define MAX_NAMES 1000

static struct name names[MAX_NAMES];
static int n_names = 0;

int declare_name(char *name)
{
	strncpy(names[n_names].name, name, 20);
	names[n_names].expr = NULL;

	n_names++;
}

int assign_name(char *n, struct sexpr *v)
{

}
struct sexpr *resolve_name(struct name n)
{
	struct sexpr *result;

	if (n.val->tag == TAG_NAME)
		result = resolve_name(n.expr->val->sexpr_name);
	else
		result = n.val;

	return result;
}	
