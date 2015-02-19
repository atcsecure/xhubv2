#include "../include/error.h"

DEFINE_OBJECT(error);

DEFINE_ERROR(error_unknown, "Unknown error, contact developer");
DEFINE_ERROR(error_invalid_argument, "Invalid argument");
DEFINE_ERROR(error_out_of_memory, "Out of memory");
DEFINE_ERROR(error_bad_operation, "Bad operation");
DEFINE_ERROR(error_end_of_file, "End of file");
DEFINE_ERROR(error_access_denied, "Access denied");
DEFINE_ERROR(error_again, "Try again later");
DEFINE_ERROR(error_in_progress, "Operation in progress");
DEFINE_ERROR(error_canceled, "Operation canceled");
DEFINE_ERROR(error_no_data, "Data not available");
