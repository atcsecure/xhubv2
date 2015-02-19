#include "eventloop_p.h"

#include <uv.h>

error_t *error_from_uv(int uv) {
	switch(uv) {
		case UV_ENOMEM:
		case UV_EAI_MEMORY:
			return error_out_of_memory;
		case UV_EINVAL:
			return error_invalid_argument;
		case UV_EOF:
			return error_end_of_file;
		case UV_EACCESS:
			return error_access_denied;
		case UV_EPERM:
			return error_bad_operation;
		case UV_EAGAIN:
		case UV_EAI_AGAIN:
			return error_again;
		case UV_EBUSY:
		case UV_EALREADY:
			return error_in_progress;
		case UV_ECANCELED:
		case UV_EAI_CANCELED:
			return error_canceled;
		default:
			return error_unknown;
	}
}
