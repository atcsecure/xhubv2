#pragma once

#include <uv.h>

#include "../include/error.h"

typedef struct {
	uv_loop_t loop;
	bool open;
} eventloop_p;

error_t *error_from_uv(int uv);
