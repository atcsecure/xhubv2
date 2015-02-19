#pragma once

#include <stdint.h>

#include "destructable.h"
#include "object.h"

typedef struct {
	object_t super;
	void *private;
} list_t;

#define list_type "list," object_type
#define list_interfaces DESTRUCTABLE(list), ITERABLE(list), object_interfaces
DECLARE_DESTRUCTABLE(list);
DECLARE_ITERABLE(list);
DECLARE_OBJECT(list);

error_t *list_construct(list_t *);

error_t *list_push(list_t *, const object_t *);
error_t *list_push_owned(list_t *, object_t *);
object_t *list_pop(list_t *);

uint32_t list_size(list_t *);
