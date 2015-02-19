#pragma once

#include "handle.h"
#include "object.h"
#include "transaction.h"

typedef struct {
	object_t super;
	void *private;
} cryptoclient_t;

#define cryptoclient_type "cryptoclient," object_type
#define cryptoclient_interfaces DESTRUCTABLE(cryptoclient), \
	HANDLE(cryptoclient), object_interfaces
DECLARE_DESTRUCTABLE(cryptoclient);
DECLARE_HANDLE(cryptoclient);
DECLARE_OBJECT(cryptoclient);

#define XCURRENCY 1
#define BLOCKNET 2

error_t *cryptoclient_construct(cryptoclient_t *, int);

int cryptoclient_id(cryptoclient_t *);

// updates transaction with signed inputs
error_t *cryptoclient_sign(cryptoclient_t *, transaction_t *);

// returns transaction id
object_t *cryptoclient_submit(cryptoclient_t *, transaction_t *);

// returns transaction
object_t *cryptoclient_get(cryptoclient_t *, transaction_id_t *);

// returns transaction id
object_t *cryptoclient_new_address(cryptoclient_t *);

// returns array of transaction inputs
object_t *cryptoclient_unspent_inputs(cryptoclient_t *);
