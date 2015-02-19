#pragma once

#include "process.h"

typedef struct {
	process_provider_t super;
	void *private;
} progressive_process_provider_t;

#define progressive_process_provider_type  "progressive_process_provider," \
	process_provider_type
#define progressive_process_provider_interface \
	DESTRUCTABLE(progressive_process_provider), process_provider_interfaces
DECLARE_DESTRUCTABLE(progressive_process_provider);
DECLARE_OBJECT(progressive_process_provider);

error_t
*progressive_process_provider_construct(progressive_process_provider_t *);

error_t
*progressive_process_provider_next_result(progressive_process_provider_t *,
                                          object_t *);

// a process with progressive results before it finishes
typedef struct {
	process_t super;
	void *private;
	error_t *(*next_result)(result_t *result);
} progressive_process_t;

#define progressive_process_type "progressive_process," process_type
#define progressive_process_interfaces DESTRUCTABLE(progressive_process), \
	process_interfaces
DECLARE_DESTRUCTABLE(progressive_process);
DECLARE_OBJECT(progressive_process);

error_t *progressive_process_construct(progressive_process_t *,
                                       progressive_process_provider_t *);
