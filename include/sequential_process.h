#pragma once

#include "process.h"

typedef struct {
	process_provider_t super;
	void *private;
} sequential_process_provider_t;

#define sequential_process_provider_type "sequential_process_provider," \
	process_provider_type
#define sequential_process_provider_interfaces \
	DESTRUCTABLE(sequential_process_provider), process_provider_interfaces
DECLARE_DESTRUCTABLE(sequential_process_provider);
DECLARE_OBJECT(sequential_process_provider);

error_t *sequential_process_provider_construct(sequential_process_t *,
                                               list_t *);
