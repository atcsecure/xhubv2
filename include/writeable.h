#pragma once

#include <stddef.h>

#include "object.h"

typedef struct {
	object_t super;
	error_t *(*write)(object_t *, void*, size_t);
	error_t *(*end)(object_t *);
} writeable_t;

#define writeable_type "writeable," object_type
#define writeable_interfaces object_interfaces
DECLARE_OBJECT(writeable);

#define DECLARE_WRITEABLE(typename) \
	error_t * typename##_write(object_t *, void *, size_t); \
	error_t * typename##_end(object_t *);
#define WRITEABLE(typename) ((object_t*)&(writeable_t){writeable_object, \
	typename##_write, typename##_end})

error_t *write(object_t *, void *, size_t);
error_t *end(object_t *);
