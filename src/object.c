#include "../include/object.h"

#include <string.h>

bool type_compare(const char *left, const char *right) {
	size_t llen = strlen(left);
	size_t rlen = strlen(right);
	size_t start_of_stricter;

	// left is the looser type
	if (llen < rlen) {
		start_of_stricter = rlen - llen;
		return strncmp(right + start_of_stricter, left, llen) == 0 ?
			true : false;
	}
	// right is the looser type
	else if (rlen < llen) {
		start_of_stricter = llen - rlen;
		return strncmp(left + start_of_stricter, right, rlen) == 0 ?
			true : false;
	}
	else {
		return strcmp(left, right) == 0 ? true : false;
	}
}

object_t** next_interface_pred(object_t **interfaces,
                               bool (*is_interface)(object_t *)) {
	assert(interfaces != NULL && is_interface != NULL);
	while (*interfaces != NULL) {
		if (is_interface(*interfaces))
			return interfaces;
		++interfaces;
	}
	return NULL;
}
