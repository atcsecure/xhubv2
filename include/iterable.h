#pragma once

typedef struct {
	object_t super;
	object_t *(*iterate)(object_t *, object_t **);
} iterable_t;

#define iterable_type "iterable," object_type
#define iterable_interfaces object_interfaces
DECLARE_OBJECT(iterable);

#define foreach(i,o) \
	for (void* sym(foreach, it) = NULL, \
	     object_t * i = iterate( o, & sym(foreach, it) ); \
	     sym(foreach, it) != NULL; \
	     i = iterate( o, & sym(foreach, it) ))

#define DECLARE_ITERABLE(typename) object_t *iterate_##typename (object_t **);
#define ITERABLE(typename) (object_t*)&(iterable_t){iterable_object, \
	iterate_##typename }

object_t *iterate(object_t *, void **);
