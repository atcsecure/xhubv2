#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "error.h"
#include "object.h"

typedef struct {
	object_t super;
	void *private;
	error_t *(*start)(process_provider_t *);
	error_t *(*cancel)(process_provider_t *);
} process_provider_t;

#define process_provider_type "process_provider," object_type
#define process_provider_interfaces DESTRUCTABLE(process_provider), \
	object_interfaces
DECLARE_DESTRUCTABLE(process_provider);
DECLARE_OBJECT(process_provider);

error_t *process_provider_construct(process_provider_t *);

error_t *process_provider_complete(process_provider_t *, object_t *);

// manages the lifetime of an asynchronous process with an eventual result
typedef struct {
	object_t super;
	void *private;
	void *userdata;
	error_t *(*done)(process_t *, object_t *);
} process_t;

#define process_type "process," object_type
#define process_interfaces DESTRUCTABLE(process), object_interfaces
DECLARE_DESTRUCTABLE(process);
DECLARE_OBJECT(process);

error_t *process_construct(process_t *, process_provider_t *);

error_t *process_start(process_t *);
error_t *process_cancel(process_t *);
bool is_process_active(const process_t *);
