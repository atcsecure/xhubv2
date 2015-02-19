#pragma once

#include <stdint.h>

#include "process.h"

typedef struct {
	process_provider_t super;
	void *private;
} parallel_process_provider_t;

#define parallel_process_provider_type "parallel_process_provider," \
	process_provider_type
#define paralell_process_provider_interfaces \
	DESTRUCTABLE(parallel_process_provider), process_provider_interfaces
DECLARE_DESTRUCTABLE(parallel_process_provider);
DECLARE_OBJECT(parallel_process_provider);

error_t *parallel_process_provider_construct(parallel_process_t *, list_t *);
