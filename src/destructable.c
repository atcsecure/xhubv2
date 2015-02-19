#include "../include/destructable.h"

#include "../include/error.h"

DEFINE_OBJECT(destructable);

void destruct(object_t *self) {
	assert(self != NULL && self->type != NULL && self->interfaces != NULL);

	// simply loop through each destructable interface
	object_t **destruct_interfaces = next_interface(self->interfaces,
	                                                destructable);
	while (*destruct_interfaces != NULL) {
		assert((*destruct_interfaces)->destruct != NULL);
		// and call it
		(*destruct_interfaces)->destruct(self);

		destruct_interfaces = next_interface(destruct_interfaces,
		                                     destructable);
	}
}
