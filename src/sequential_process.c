#include "../include/sequential_process.h"

typedef struct {
	list_t *results;
	list_t *processes;
	void *it;
} private_t;

error_t *nextprocdone(process_t *self, object_t *result) {
	assert(self != NULL && self->userdata != NULL);
	process_provider_t *provider;
	private_t *private;
	error_t *err;

	provider = self->userdata;
	assert(provider->private != NULL);
	private = provider->private;
	assert(private->processes != NULL && private->results != NULL);

	err = list_push(private->results, result);
	if (err != NULL) return err;

	object_t *obj = list_iterate(private->processes, &it);
	if (is_error(obj)) return obj;
	else if (obj == NULL) {
		err = process_provider_complete(provider, private->results);
		if (err != NULL) return err;
		return NULL;
	}

	assert(is_process(obj));
	process_t *proc = obj;
	proc->done = nextprocdone;
	proc->userdata = provider;

	err = process_start(proc);
	if (err != NULL) return err;

	return NULL;
}

error_t *sequential_process_provider_start(sequential_process_provider_t
                                           *provider) {
	private_t *private;
	error_t *err;
	assert (provider != NULL);

	private = provider->private;
	assert(private->processes != NULL && private->results != NULL);

	object_t *obj = list_iterate(private->processes, &it);
	if (is_error(obj)) return obj;

	assert(obj != NULL && is_process(obj));
	process_t *proc = obj;
	proc->done = nextprocdone;
	proc->userdata = provider;

	err = process_start(proc);
	if (err != NULL) return err;

	return NULL;
}

error_t *sequential_process_provider_cancel(sequential_process_provider_t
                                            *self) {
	private_t *private;
	error_t *err;

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

int sequential_process_provider_construct(sequential_process_provider_t *self,
                                          list_t *processes) {
	error_t *err;
	private_t *private;

	assert (self != NULL && processes != NULL);

	err = process_provider_construct(self);
	if (ret != NULL) return err;

	self->parent->start = sequential_process_provider_start;
	self->parent->cancel = sequential_process_provider_cancel;

	INIT_OBJECT(self, sequential_process_provider);

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

int sequential_process_provider_destruct(object_t *obj) {
	private_t *private;
	sequential_process_provider_t *self = obj;

	if (self != NULL) {
		assert(is_sequential_process_provider(self));

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
