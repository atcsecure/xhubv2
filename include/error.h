#pragma once

#include <stdbool.h>

#include "object.h"

// Errors that are easily fixable by a programmer, like a NULL argument, should
// use assert. If these assertable errors are the only sources of errors in your
// program, you should skip this system altogether!

typedef struct {
	object_t super;
	const char *name;
	const char *message;
} error_t;

#define error_type "error," object_type
#define error_interfaces object_interfaces
DECLARE_OBJECT(error);

// helper to initialize constant global errors (this should be all of them)
#define DEFINE_ERROR(NAME, MSG) NAME = &(error_t) { error_object, #NAME, (MSG) }

const error_t *error_unknown;
const error_t *error_invalid_argument;
const error_t *error_out_of_memory;
const error_t *error_bad_operation;
const error_t *error_end_of_file;
const error_t *error_access_denied;
const error_t *error_again;
const error_t *error_in_progress;
const error_t *error_canceled;
const error_t *error_no_data;
