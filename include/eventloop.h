#pragma once

#include <stdbool.h>

#include "handle.h"
#include "object.h"

typedef struct {
	object_t super;
	void *private;
} eventloop_t;

#define eventloop_type "eventloop," object_type
#define eventloop_interfaces DESTRUCTABLE(eventloop), HANDLE(eventloop), \
	object_interfaces
DECLARE_DESTRUCTABLE(eventloop);
DECLARE_HANDLE(eventloop);
DECLARE_OBJECT(eventloop);

error_t *eventloop_construct(eventloop_t *);

// runs the eventloop once, optionally waiting for events
object_t *eventloop_run(eventloop_t *, bool);
