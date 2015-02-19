#pragma once

#include <stdint.h>

#include "process.h"

typename struct {
	process_t super;
	void *private;
} query_t;

#define query_type "query," process_type
#define query_interfaces DESTRUCTABLE(query), process_interfaces
DECLARE_DESTRUCTABLE(query);
DECLARE_OBJECT(query);

error_t *query_construct(query_t *, object_t *, const char *, uint16_t);
