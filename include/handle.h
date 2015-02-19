#pragma once

#include "object.h"

typedef struct {
	object_t super;
	error_t *(*open)(object_t *, process_t *);
	error_t *(*close)(object_t *, process_t *);
	char     (*is_open)(const object_t *);
} handle_t;

#define handle_type "handle," object_type
#define handle_interfaces object_interfaces
DECLARE_OBJECT(handle);

#define DECLARE_HANDLE(typename) \
	error_t * typename##_open(object_t *, process_t *); \
	error_t * typename##_close(object_t *, process_t *); \
	bool is_##typename##_open(const object_t *);

#define HANDLE(typename) &(handle_t){handle_object, typename##_open, \
	typename##_close, is_##typename##_open}

error_t *open(object_t *, process_t *);
error_t *close(object_t *, process_t *);
char     is_open(object_t *);
