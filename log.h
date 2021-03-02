#ifndef _LOG_H
#define _LOG_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum log_level_t {
    DEBUG = 1,
    INFO,
    WARNING,
    ERROR
} log_level;

extern void init_log(log_level log_mask, const char *log_file_name, int max_size_by_Mbytes, int max_rotate_number);
extern void print_log(log_level lvl, char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif // _LOG_H