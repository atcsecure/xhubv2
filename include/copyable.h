#pragma once

#include "object.h"

typedef struct {
	object_t super;
	const char *implementing_type;
	object_t *(*copy)(object_t *);
} copyable_t;

#define copyable_type "copyable," object_type
#define copyable_interfaces object_interfaces
DECLARE_OBJECT(copyable);

#define DECLARE_COPYABLE(typename) object_t * typename##_copy(object_t *)
#define COPYABLE(typename) (&(copyable_t){copyable_object, typename##_type, \
                            typename##_copy})

object_t *copy(object_t *);
