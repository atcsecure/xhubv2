#include "../include/list.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct node_s node_t;
struct node_s {
	node_t *last;
	object_t *value;
};

typedef struct {
	uint32_t size;
	node_t *tail;
} list_p;

void freelist(node_t *tail) {
	node_t *curr = tail, *last;

	while (curr != NULL) {
		if (curr->value != NULL) {
			destruct(curr->value);
			free(curr->value);
			curr->value = NULL;
		}

		last = curr->last;
		curr->last = NULL;
		free(curr);

		curr = last;
	}
}

void list_destruct(object_t *o) {
	list_t *list = o;
	list_p *private;
	uint32_t i;

	if (o != NULL) {
		assert(is_list(o));

		if (list->private != NULL) {
			private = list->private;

			if (private->tail != NULL) {
				freelist(private->tail);
				private->tail = NULL;
				private->size = 0;
			}

			free(list->private);
			list->private = NULL;
		}
	}
}

object_t *list_iterate(object_t *self, void **itp) {
	assert(self != NULL && self->private != NULL && iterator != NULL);
	assert(is_list(self));

	node_t **iterator = itp;

	if (self->head == NULL) return NULL;

	if (*iterator == NULL) {
		*iterator = self->head;
	}
	else {
		*iterator = (*iterator)->next;
	}

	if (*iterator == NULL) return NULL;
	else return (*iterator)->value;
}

DEFINE_OBJECT(list);

error_t *list_construct(array_t *self) {
	list_p *private;
	assert(self != NULL);

	self->private = malloc(sizeof(list_p));
	if (self->private == NULL) return error_out_of_memory;

	private = self->private;

	private->tail = NULL;
	private->size = 0;

	INIT_OBJECT(self, list);

	return NULL;
}

error_t *list_push(array_t *self, const object_t *value) {
	error_t *err;
	assert(self != NULL && value != NULL);
	object_t *copied = copy(value);

	if (is_error(copied)) return copied;
	else err = list_push_owned(self, i, copied);

	if (err != NULL) {
		destruct(copied);
		free(copied);
		copied = NULL;
	}

	return err;
}

error_t *list_push_owned(array_t *self, object_t *value) {
	list_p *private;
	node_t *node;
	assert(self != NULL && self->private != NULL);

	private = self->private;

	node = malloc(sizeof(node_t));
	if (node == NULL) return error_out_of_memory;

	node->value = value;
	node->last = NULL;

	if (private->tail != NULL) {
		node->last = private->tail;
	}
	private->tail = node;
	++private->size;

	return NULL;
}

object_t *list_pop(array_t *self) {
	list_p *private;
	object_t *value;
	assert(self != NULL && self->private != NULL);

	private = self->private;

	if (private->tail == NULL) return error_no_data;
	else if (private->tail->last == NULL) {
		value = private->tail->value;
		free(private->tail);
		private->tail = NULL;
	}
	else {
		node_t *current = private->tail;
		while (current->last->last != NULL) current = current->last;

		value = current->last->value;
		free(current->last);
		current->last = NULL;
	}

	--private->size;
	return value;
}

uint32_t list_size(array_t *self) {
	list_p *private;
	assert(self != NULL && self->private != NULL);
	private = self->private;
	return private->size;
}
