#ifndef _LOG_H
#define _LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

typedef enum log_level_t {
    ERROR = 1,
    WARNING,
    INFO,
    DEBUG
} log_level;

typedef struct log_t {
    log_level log_mask;
    char *log_file;
} log;

extern void init_log(log_level log_mask, const char *log_file_name, int max_size_by_Mbytes, int max_rotate_number);
extern void log(log_level lvl, char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif // _LOG_H