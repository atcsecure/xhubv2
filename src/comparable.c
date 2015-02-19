#include "../include/comparable.h"

#include "../include/error.h"

DEFINE_OBJECT(comparable);

object_t *compare(object_t *left, object_t *right) {
	assert(left != NULL && right != NULL && left->type != NULL &&
	       right->type != NULL && left->interfaces != NULL &&
	       right->interfaces != NULL);

	// firstly, compare type
	if (strcmp(left->type, right->type) != 0) return bool_false();

	// next, get the first comparable interface
	object_t **compare_interfaces = next_interface(left->interfaces,
	                                              comparable);

	// if there isn't a single comparable interface, then these cannot be
	// compared
	if (compare_interfaces == NULL) {
		return error_bad_operation;
	}

	// for each valid comparable interface
	while (compare_interfaces != NULL) {
		assert((*compare_interfaces)->compare != NULL);

		// do the comparison
		object_t *ret = (*compare_interfaces)->compare(left, right);
		if (is_error(ret)) return ret;

		// return false when the first comparison returns false
		if (!is_true(ret)) return bool_false();

		compare_interfaces = next_interface(compare_interfaces,
		                                    comparable);
	}

	// this means each comparison worked
	return bool_true();
}
