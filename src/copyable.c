#include "../include/copyable.h"

#include "../include/error.h"

DEFINE_OBJECT(copyable);

object_t *copy(object_t *self) {
	assert(self != NULL && self->type != NULL && self->interfaces != NULL);

	// try to find the copyable interface
	object_t **copy_interfaces = next_interface(self->interfaces, copyable);

	if (copy_interface == NULL) {
		return error_bad_operation;
	}

	// this copy interface is for a parent type, and it won't work here
	if (strcmp((*copy_interface)->implementing_type, self->type) != 0) {
		return error_bad_operation;
	}

	assert((*copy_interface)->copy != NULL)
	return (*copy_interface)->copy(self);
}
