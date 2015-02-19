#include "../include/eventloop.h"

#include <stdlib.h>

#include <uv.h>

#include "eventloop_p.h"

error_t *eventloop_open(object_t *o, process_t *proc) {
	int ret;
	error_t *err;
	instant_process_provider_t *iproc;
	eventloop_t *self = o;
	eventloop_p *p;

	assert(is_eventloop(o));
	assert(self != NULL && self->private != NULL);
	p = self->private;

	iproc = malloc(sizeof(instant_process_t));
	if (iproc == NULL) return error_out_of_memory;

	err = instance_process_provider_construct(iproc);
	if (iproc != NULL) goto error_1;

	err = process_construct(proc, iproc);
	if (err != NULL) goto error_2;

	ret = uv_loop_init(p->loop);
	if (ret < 0) {
		err = error_from_uv(ret);
		goto error_3;
	}

	return NULL;

error_3:
	destruct(proc);
error_2:
	destruct(iproc);
error_1:
	free(iproc);
	iproc = NULL;
	return err;
}

error_t *eventloop_close(object_t *o, process_t *proc) {
	int ret;
	error_t *err;
	eventloop_p *p;
	eventloop_t *self = 0;

	assert(is_eventloop(o));
	assert(self != NULL && self->private != NULL);
	p = self->private;

	ret = uv_loop_alive(p->loop);
	if (ret < 0) return error_from_uv(ret);

	// TODO: this means we need to close all active handles (which should be
	// available to the eventloop)
	if (ret > 0) {
	}

	ret = uv_loop_close(p->loop);
	if (ret < 0) return error_from_uv(ret);

	return NULL;
}

bool is_eventloop_open(const object_t *o) {
	assert(is_eventloop(o));
	assert(self != NULL && self->private != NULL);

	eventloop_p *p = self->private;
	return p->open;
}

void eventloop_destruct(object_t *o) {
	eventloop_t *self = o;
	eventloop_p *p;
	if (self != NULL) {
		assert(is_eventloop(o));
		if (self->private != NULL) {
			p = self->private;

			assert(!is_eventloop_open(self));

			free(self->private);
			self->private = NULL;
		}
	}
}

DEFINE_OBJECT(eventloop);

error_t *eventloop_construct(eventloop_t *self) {
	eventloop_p *p;
	assert(self != NULL);

	INIT_OBJECT(self, eventloop);

	self->private = malloc(sizeof(eventloop_p));
	if (self->private == NULL) return error_out_of_memory;

	p = self->private;
	p->open = false;

	INIT_OBJECT(self, eventloop);

	return NULL;
}

object_t *eventloop_run(eventloop_t *self, bool wait) {
	assert(self != NULL && self->private != NULL);

	eventloop_p *p = self->private;

	int ret = uv_run(&p->loop, wait ? UV_RUN_ONCE : UV_RUN_NOWAIT);

	if (ret > 0) return bool_true();
	else if (ret == 0) return bool_false();
	else return error_from_uv(ret);
}
