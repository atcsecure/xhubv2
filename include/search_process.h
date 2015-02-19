#pragma once

#include <stdint.h>

#include "process.h"

typedef struct {
	process_provider_t super;
	void *private;
	double timeout; // in seconds
	const char *disctype; // the type of discovery for which to search
	uint16_t minimum_users;
	uint16_t maximum_users;
} search_process_provider_t;

#define search_process_provider_type "search_process_provider," \
	process_provider_type
#define search_process_provider_interfaces \
	DESTRUCTABLE(search_process_provider), process_provider_interfaces
DECLARE_DESTRUCTABLE(search_process_provider);
DECLARE_OBJECT(search_process_provider);

error_t *search_process_provider_construct(search_process_provider_t *);

typedef struct {
	object_t super;
	const char *host;
	uint16_t port;
} search_process_result_t;

#define search_process_result_type "search_process_result," object_type
#define search_process_result_interfaces DESTRUCTABLE(search_process_result), \
	object_interfaces
DECLARE_DESTRUCTABLE(search_process_result);
DECLARE_OBJECT(search_process_result);
