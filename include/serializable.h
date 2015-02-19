#pragma once

#include "object.h"

typedef struct {
	object_t super;
	object_t *(*serialize)(object_t *);
	object_t *(*deserialize)(object_t *);
} serializable_t;

#define serializable_type "serializable," object_type
#define serializable_interfaces object_interfaces
DECLARE_OBJECT(serializable);

#define DECLARE_SERIALIZABLE(typename) \
	object_t * typename##_serialize(object_t *); \
	object_t * typename##_deserialize(object_t *)

#define SERIALIZABLE(typename) (&(serializable_t){serializable_object, \
	typename##_serialize, typename##_deserialize})

object_t *serialize(object_t *);
object_t *deserialize(object_t *);
