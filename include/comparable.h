#pragma once

#include "object.h"

typedef struct {
	object_t super;
	object_t *(*cmp)(object_t *, object_t *);
} comparable_t;

#define comparable_type "comparable," object_type
#define comparable_interfaces object_interfaces
DECLARE_OBJECT(comparable);

#define DECLARE_COMPARABLE(typename) \
	object_t * typename##_compare(object_t *, object_t *)
#define COMPARABLE(typename) (&(comparable_t){comparable_object, \
	typename##_compare})

object_t *compare(object_t *, object_t *);
