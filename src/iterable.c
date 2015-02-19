#include "../include/iterable.h"

object_t *iterate(object_t *coll, void **itp) {
	assert(coll != NULL && itp != NULL && coll->interfaces != NULL);

	object_t **iterate_interfaces
		= next_interface(coll->interfaces, iterable);

	if (iterate_interfaces == NULL) {
		return error_bad_operation;
	}

	assert((*iterate_interfaces)->iterate != NULL);
	return (*iterate_interfaces)->iterate(coll, itp);
}
