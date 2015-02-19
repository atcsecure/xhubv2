#include "../include/writeable.h"

error_t *write(object_t *obj, void *buff, size_t size) {
	assert(obj != NULL && buff != NULL && size > 0 &&
	       obj->interfaces != NULL);

	object_t **writeable_interfaces
		= next_interface(obj->interfaces, writeable);

	if (writeable_interfaces == NULL) {
		return error_bad_operation;
	}

	assert((*writeable_interfaces)->write != NULL);
	return (*writeable_interfaces)->write(obj, buff, size);
}

error_t *end(object_t *obj) {
	assert(obj != NULL && obj->interfaces != NULL);

	object_t **writeable_interfaces
		= next_interface(obj->interfaces, writeable);

	if (writeable_interfaces == NULL) {
		return error_bad_operation;
	}

	assert((*writeable_interfaces)->end != NULL);
	return (*writeable_interfaces)->end(obj);
}
