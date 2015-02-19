#pragma once

#include <stdint.h>

#include "eventloop.h"
#include "progressive_process.h"

typedef struct {
	progressive_process_t parent;
	void *private;
} tcp_server_t;

#define tcp_server_type "tcp_server," progressive_process_type
#define tcp_server_interfaces DESTRUCTABLE(tcp_server), HANDLE(tcp_server), \
	progressive_process_interfaces
DECLARE_DESTRUCTABLE(tcp_server);
DECLARE_HANDLE(tcp_server);
DECLARE_OBJECT(tcp_server);

error_t *tcp_server_construct(tcp_server_t *, eventloop_t *, const char *,
                              uint16_t);
