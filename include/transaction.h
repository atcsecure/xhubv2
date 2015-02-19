#pragma once

#include <stdint.h>

#include "object.h"

typedef struct {
	object_t super;
	uint64_t data[4];
} transaction_id_t;

#define transaction_id_type "transaction_id," object_type
#define transaction_interfaces object_interfaces
DECLARE_OBJECT(transaction_id);

typedef struct {
	object_t super;
	char address[36];
	int64_t amount;
} transaction_output_t;

#define transaction_output_type "transaction_output," object_type
#define transaction_output_interfaces object_interfaces
DECLARE_OBJECT(transaction_output);

typedef struct {
	object_t super;
	transaction_id_t tx;
	int vout;
} transaction_input_t;

#define transaction_input_type "transaction_input," object_type
#define transaction_input_interfaces object_interfaces
DECLARE_OBJECT(transaction_input);

typedef struct {
	object_t super;
	time_t *expiration;
	list_t *inputs;
	list_t *outputs;
} transaction_t;

#define transaction_type "transaction," object_type
#define transaction_interfaces DESTRUCTABLE(transaction), object_interfaces
DECLARE_DESTRUCTABLE(transaction);
DECLARE_OBJECT(transaction);
