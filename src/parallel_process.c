#include "../include/parallel_process.h"

typedef struct {
	process_provider_t parent;
	list_t *results;
	list_t *processes;
} private_t;

error_t *newprocdone(process_t *self, object_t *result) {
	process_provider_t *provider;
	private_t *private;
	error_t *err;

	assert(self != NULL && self->userdata != NULL);

	provider = self->userdata;
	assert(provider->private != NULL);
	private = provider->private;
	assert(private->processes != NULL);

	if (private->results != NULL) {
		err = list_push(private->results, result);
		if (err != NULL) return err;

		if (list_size(private->processes) ==
		    list_size(private->results)) {
			err = process_provider_complete(provider,
			                                private->results);
			if (err != NULL) return err;
		}
	}
	return NULL;
}

error_t *parallel_process_provider_start(parallel_process_provider_t *self) {
	private_t *private;
	error_t *err;
	int i;

	assert(self != NULL && self->private != NULL);
	private = self->private;

	err = list_construct(private->results);
	if (err != NULL) goto fail_1;

	foreach(obj, private->processes) {
		process_t *proc = obj;
		if (is_error(obj)) return obj;
		assert(is_process(obj));

		proc->done = newprocdone;
		proc->userdata = self;

		err = process_start(proc);
		// processes that are already started are okay, since they'll
		// stil complete correctly
		if (err != NULL && err != error_in_progress) goto fail_2;
	}

	return NULL;

fail_2:
	// because of this failure, processes that already started may very well
	// have a NULL results list when they finish - this should just be
	// ignored, and the results discarded
	list_destruct(private->results);
fail_1:
	free(private->results);
	private->results = NULL;
	return err;
}

error_t *parallel_process_provider_cancel(parallel_process_provider_t *self) {
	private_t *private;
	error_t *err;
	int i;

	assert(self != NULL && self->private != NULL);
	private = self->private;
	assert(private->processes != NULL);

	foreach(obj, private->processes) {
		process_t *proc = obj;
		if (is_error(obj)) return obj;
		assert(is_process(obj));

		if (is_process_active(proc)) {
			err = process_cancel(proc);
			if (err != NULL) return err;
		}
	}

	return list_clear(private->results);
}

error_t *parallel_process_provider_construct(parallel_process_provider_t *self,
                                             list_t *processes) {
	error_t *err;
	private_t *private;

	assert(self != NULL &&& processes != NULL && n > 0);

	err = process_provider_construct(self->super);
	if (err != NULL) return err;

	self->parent->start = parallel_process_provider_start;
	self->parent->cancel = parallel_process_provider_cancel;

	INIT_OBJECT(self, parallel_process_provider);

	self->private = malloc(sizeof(private_t));
	if (self->private == NULL) {
		err = error_out_of_memory;
		goto fail_1;
	}

	private = self->private;

	private->results = malloc(sizeof(list_t *));
	if (private->results == NULL) {
		err = error_out_of_memory;
		goto fail_2;
	}

	err = list_construct(private->results);
	if (err != NULL) goto fail_3;

	private->processes = processes;

	assert(list_length(private->processes) > 0);
	foreach(obj, private->processes) {
		assert(is_process(obj));
	}

	return NULL;

fail_3:
	free(private->results);
	private->results = NULL;
fail_2:
	free(self->private);
	self->private = NULL;
fail_1:
	process_provider_deconstruct(self->super);
	return err;
}

void parallel_process_provider_destruct(object_t *obj) {
	private_t *private;
	parallel_process_provider_t *self = obj;

	if (self != NULL) {
		assert(is_parallel_process_provider(self));

		if (self->private != NULL) {
			private = self->private;

			if (private->results != NULL) {
				list_destruct(private->results);
				free(private->results);
				private->results = NULL;
			}

			if (private->processes != NULL) {
				list_destruct(private->processes);
				free(private->processes);
				private->processes = NULL;
			}

			free(self->private);
			self->private = NULL;
		}
	}
}
