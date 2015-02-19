#pragma once

#include "process.h"

typedef struct {
	process_provider_t super;
} instant_process_provider_t;

#define instant_process_provider_type "instant_process_provider," \
	process_provider_type
#define instant_process_provider_interfaces object_interfaces
DECLARE_OBJECT(instant_process_provider);

error_t *instant_process_provider_construct(instant_process_provider_t *);
