#pragma once

#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#define sym(mac, var) ___##mac##_##var##_##__LINE__

typedef struct object_s object_t;

struct object_s {
	// you should set this to something no one else will ever use (probably due
	// to a namespace collision) - used for downcasting
	const char  *type;
	void         (*const destruct)(object_t *);
	object_t **const interfaces;
};

#define object_type "object"
#define object_interfaces NULL

#define INIT_OBJECT(self, typename) \
	((*((object_t*)self)) = typename##_object)

bool type_compare(const char *, const char *);

#define DECLARE_OBJECT(typename) \
	bool is_##typename (const object_t *);\
	bool is_##typename##_instance(const object_t *); \
	const object_t typename##_object = {\
		typename##_type, \
		{typename##_interfaces} \
	}

#define DEFINE_OBJECT(typename) \
	bool is_##typename (const object_t *self) {\
		assert(self != NULL && self->type != NULL); \
		return type_compare( typename##_type, self->type); \
	}\
	bool is_##typename##_instance(const object_t *self) {\
		assert(self != NULL && self->type != NULL); \
		return strcmp( typename##_type, self->type) == 0 \
		       ? true : false; \
	}

object_t** next_interface_pred(object_t **, bool (*)(object_t *));
#define next_interface(interfaces, interface) \
	next_interface_pred(interfaces, is_##interface )
