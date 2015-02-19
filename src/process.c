#include "../include/process.h"
#include "../include/error.h"

#include <stdlib.h>

typedef struct {
	process_t *process;
} process_provider_p;

void process_provider_destruct(object_t *self) {
	if (self != NULL) {
		assert(is_process_provider_instance(self));

		if (self->private != NULL) {
			free(self->private);
			self->private = NULL;
		}
	}
}

DEFINE_OBJECT(process_provider);

error_t *process_provider_construct(process_provider_t *self) {
	assert(self != NULL);

	INIT_OBJECT(self, process_provider);

	self->private = malloc(sizeof(process_provider_p));
	self->start = NULL;
	self->cancel = NULL;
	self->userdata = NULL;

	if (self->private == NULL) return error_out_of_memory;

	process_provider_p *pr = self->private;
	pr->process = NULL;

	return NULL;
}

typedef struct {
	process_provider_t *provider;
	bool active;
	object_t *result;
} process_p;

error_t *process_provider_complete(process_provider_t *self, object_t *result) {
	assert(self != NULL && self->private != NULL);
	process_provider_p *pr = self->private;

	// this should never happen because you shouldn't complete the provider
	// until after it has been started, which only occurs when it's part of
	// a process
	assert(pr->process != NULL);

	process_p *pp = pr->process->private;
	pp->active = false;
	pp->result = result;
	if (pr->process->done != NULL) pr->process->done(result);
	return NULL;
}

void process_destruct(object_t *self) {
	process_p *pp;
	process_t *pt;

	if (self != NULL) {
		assert(is_process(self));

		pt = self;
		if (pt->private != NULL) {
			pp = pt->private;

			if (pp->provider != NULL) {
				process_provider_destruct(pp->provider);
				free(pp->provider);
				pp->provider = NULL;
			}

			free(pt->private);
			pt->private = NULL;
		}
	}
}

DEFINE_OBJECT(process);

error_t *process_construct(process_t *self, process_provider_t *provider) {
	assert(self != NULL && provider != NULL && provider->private != NULL);

	INIT_OBJECT(self, process);

	self->private = malloc(sizeof(process_p));
	self->done = NULL;
	self->user_data = NULL;

	if (self->private == NULL) return error_out_of_memory;

	process_p *p = self->private;
	pr->provider = provider;

	process_provider_p *providerp = pr->provider->private;
	providerp->process = self;

	return NULL;
}

error_t *process_start(process_t *self) {
	process_p *pr;
	assert(self != NULL && self->private != NULL);

	pr = self->private;
	assert(pr->provider != NULL);

	// starting an active process silently does nothing
	if (pr->active == true) {
		return error_in_progress;
	}

	if (pr->result != NULL && self->done != NULL) {
		return self->done(self, pr->result);
	}

	// all providers must provide a start function
	assert(pr->provider->start != NULL);

	pr->active = true;
	return pr->provider->start(pr->provider);
}

error_t *process_cancel(process_t *self) {
	process_p *pr;
	assert(self != NULL && self->private != NULL);

	pr = self->private;
	assert(pr->provider != NULL);

	if (pr->active == false) {
		return NULL;
	}

	if (pr->provider->cancel != NULL) {
		pr->active = false;
		return pr->provider->cancel(pr->provider);
	}
	else {
		// not all processes need provide a cancel function
		return error_bad_operation;
	}
}

bool is_process_active(const process_t *self) {
	process_p *pr;
	assert(self != NULL && self->private != NULL);

	pr = self->private;

	return pr->active;
}
