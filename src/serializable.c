#include "../include/serializable.h"

object_t *serialize(object_t *obj) {
	assert(obj != NULL && obj->interfaces != NULL);

	object_t **serializable_interfaces
		= next_interface(obj->interfaces, serializable);

	if (serializable_interfaces == NULL) {
		return error_bad_operation;
	}

	assert((*serializable_interfaces)->serialize != NULL);
	return (*serializable_interfaces)->serialize(obj);
}

object_t *deserialize(object_t *obj) {
	assert(obj != NULL && obj->interfaces != NULL);

	object_t **serializable_interfaces
		= next_interface(obj->interfaces, serializable);

	if (serializable_interfaces == NULL) {
		return error_bad_operation;
	}

	assert((*serializable_interfaces)->deserialize != NULL);
	return (*serializable_interfaces)->deserialize(obj);
}
