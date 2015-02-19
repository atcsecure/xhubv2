#include "../include/instant_process.h"

DEFINE_OBJECT(instant_process_provider);

error_t *ipstart(process_provider_t *self) {
	assert(self != NULL);
	return process_provider_complete(self, NULL);
}

error_t *instant_process_provider_construct(instant_process_provider_t *self) {
	error_t *err;
	assert(self != NULL);

	INIT_OBJECT(self, instant_process_provider);

	err = process_provider_construct(self->super);
	if (err != NULL) return err;

	self->super.start = ipstart;

	return NULL;
}
