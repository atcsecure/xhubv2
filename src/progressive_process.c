#include "../include/process.h"

typedef struct {
	progressive_process_provider_t *prov;
} progressive_process_p;

typedef struct {
	progressive_process_t *proc;
} progressive_process_provider_p;

void progressive_process_provider_destruct(object_t *self) {
	if (self != NULL) {
		assert(is_progressive_process_provider(self));
		if (self->private != NULL) {
			free(self->private);
			self->private = NULL;
		}
	}
}

error_t *progressive_process_provider_construct(progressive_process_provider_t
                                           *self) {
	assert(self != NULL);

	INIT_OBJECT(self, progressive_process_provider);

	self->private = malloc(sizeof(progressive_process_provider_p));
	if (self->private == NULL) return error_out_of_memory;

	return NULL;
}

error_t *progressive_process_provider_next_result(progressive_process_provider_t
                                             *self, object_t *res) {
	assert(self != NULL && self->private != NULL && res != NULL);
	progressive_process_provider_p *p;

	p = self->private;
	assert(p->proc != NULL);

	if (p->proc->next_result != NULL) return p->proc->next_result(res);
	return NULL;
}

error_t *progressive_process_construct(progressive_process_t *self,
                                  progressive_process_provider_t *prov) {
	error_t *err;
	progressive_process_p *p;
	assert(self != NULL && prov != NULL);

	INIT_OBJECT(self, progressive_process);

	self->private = malloc(sizeof(progressive_process_p));
	if (self->private == NULL) return error_out_of_memory;

	err = process_construct(self, prov);
	if (err != NULL) goto fail_1;

	p = self->private;

	p->prov = prov;
	p->prov->proc = self;
	self->next_result = NULL;

	return NULL;

fail_1:
	free(self->private);
	self->private = NULL;
	return err;
}

int progressive_process_destruct(object_t *self) {
	if (self != NULL) {
		assert(is_progressive_process(self));
		if (self->private != NULL) {
			free(self->private);
			self->private = NULL;
		}
	}
}
