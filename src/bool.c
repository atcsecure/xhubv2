#include "../include/bool.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

object_t *bool_compare(const object_t *self, const object_t *other) {
	assert(self != NULL && other != NULL);

	if (!is_bool(self) || !is_bool(other))
		return error_invalid_argument;

	bool_t *s = self, *o = other;

	return to_bool(s->value == o->value);
}

DEFINE_OBJECT(bool);

error_t *bool_construct(bool_t *self, bool value) {
	assert(self != NULL);

	INIT_OBJECT(self, bool);
	self->value = value;

	return self;
}

object_t *bool_false() {
	bool_t *new = malloc(sizeof(bool_t));
	if (new == NULL) return error_out_of_memory;

	error_t *err = bool_construct(new, false);
	if (err != NULL) {
		free(new);
		return err;
	}

	return new;
}

object_t *bool_true() {
	bool_t *new = malloc(sizeof(bool_t));
	if (new == NULL) return error_out_of_memory;

	error_t *err = bool_construct(new, true);
	if (err != NULL) {
		free(new);
		return err;
	}

	return new;
}

bool is_true(const bool_t *self) {
	assert(self != NULL);
	return self->value;
}
