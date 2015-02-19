#pragma once

#include "process.h"

typedef struct {
	process_provider_t super;
	void *private;
} exchange_process_provider_t;

#define exchange_provider_type "exchange_process_provider," \
	process_provider_type
#define exchange_provider_interfaces DESTRUCTABLE(exchange_process_provider), \
	process_provider_interfaces
DECLARE_DESTRUCTABLE(exchange_process_provider);
DECLARE_OBJECT(exchange_process_provider);

error_t *exchange_process_provider_construct(exchange_process_provider_t *);
