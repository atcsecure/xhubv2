#pragma once

#include <stdbool.h>

#include "comparable.h"
#include "error.h"
#include "object.h"

typedef struct {
	object_t super;
	bool value;
} bool_t;

#define bool_type "bool," object_type
#define bool_interfaces COMPARABLE(bool), object_interfaces
DECLARE_COMPARABLE(bool);
DECLARE_OBJECT(bool);

error_t *bool_construct(bool_t *, bool);

object_t *bool_false();
object_t *bool_true();
#define to_bool(v) ((v) ? bool_true() : bool_false())

bool is_true(const bool_t *);
