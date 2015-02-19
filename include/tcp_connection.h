#pragma once

#include <stdint.h>

#include "eventloop.h"
#include "progressive_process.h"
#include "writeable.h"

typedef struct {
	progressive_process_t super;
	void *private;
} tcp_connection_t;

#define tcp_connection_type "tcp_connection," object_type
#define tcp_connection_interfaces DESTRUCTABLE(tcp_connection), \
	HANDLE(tcp_connection), WRITEABLE(tcp_connection), object_interfaces
DECLARE_DESTRUCTABLE(tcp_connection);
DECLARE_HANDLE(tcp_connection);
DECLARE_WRITEABLE(tcp_connection);
DECLARE_OBJECT(tcp_connection);

error_t *tcp_connection_construct(tcp_connection_t *, eventloop_t *,
                                  const char *, uint16_t);
