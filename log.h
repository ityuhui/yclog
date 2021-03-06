#ifndef _LOG_H
#define _LOG_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum log_level_t {
    CL_DEBUG = 1,
    CL_INFO,
    CL_WARNING,
    CL_ERROR
} log_level;

extern void init_log(log_level log_mask, bool print_to_stderr, const char *log_file_name, int max_size_by_Mbytes, int max_rotate_number);
extern void print_log(log_level lvl, char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif // _LOG_H