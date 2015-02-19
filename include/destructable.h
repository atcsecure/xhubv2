#pragma once

#include "object.h"

typedef struct {
	object_t super;
	void (*destruct)(object_t *);
} destructable_t;

#define destructable_type "destructable," object_type
#define destructable_interfaces object_interfaces
DECLARE_OBJECT(destructable);

#define DECLARE_DESTRUCTABLE(typename) void typename##_destruct(object_t *);
#define DESTRUCTABLE(typename) ((object_t*)&(destructable_t) { \
	destructable_object, typename##_destruct})

void destruct(object_t *);
