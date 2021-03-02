#include "log.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdbool.h>

#define VL_BUFFER_SIZE 1024

typedef struct logger_t {
    log_level log_mask;
    char *log_file;
    int max_size_by_Mbytes_per_file;
    int max_rotate_number;
    bool print_to_stderr;
} logger;

static logger g_logger;

static char * log_level_to_string(log_level level)
{
    char *levels[] = {"", "DEBUG", "INFO", "WARNING", "ERROR"};
    return levels[level];
}

static void get_current_time(char *buffer, int buffer_size)
{
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep;
    struct tm *p;
    time(&timep);
    p=localtime(&timep);
    snprintf(buffer,buffer_size,
        "%d-%02d-%02d %s %02d:%02d:%02d", 
        1900 + p->tm_year,
        1 + p->tm_mon, 
        p->tm_mday,
        wday[p->tm_wday],
        p->tm_hour, 
        p->tm_min, 
        p->tm_sec);
}

static void rotate_log_file()
{

}

void init_log(log_level log_mask, bool print_to_stderr, const char *log_file_name, int max_size_by_Mbytes_per_file, int max_rotate_number)
{
    g_logger.log_mask = log_mask;
    g_logger.print_to_stderr = print_to_stderr;
    g_logger.log_file = strdup(log_file_name);
    g_logger.max_size_by_Mbytes_per_file = max_size_by_Mbytes_per_file;
    g_logger.max_rotate_number = max_rotate_number;
}

void print_log(log_level lvl, char *fmt, ...)
{
    if (lvl < g_logger.log_mask) {
        return;
    }

    char buffer[VL_BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    va_list vl;
    va_start(vl, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, vl);
    va_end(vl);

    char buffer_timestamp[VL_BUFFER_SIZE];
    memset(buffer_timestamp, 0, sizeof(buffer_timestamp));
    get_current_time(buffer_timestamp, sizeof(buffer_timestamp));

    char buffer_with_timestamp[VL_BUFFER_SIZE];
    memset(buffer_with_timestamp, 0, sizeof(buffer_with_timestamp));
    snprintf(buffer_with_timestamp, sizeof(buffer_with_timestamp), "%s [%s] %s", 
        buffer_timestamp, 
        log_level_to_string(lvl), 
        buffer);
    
    rotate_log_file();

    FILE *fp = fopen(g_logger.log_file, "a");
    fprintf(fp, "%s", buffer_with_timestamp);
    fclose(fp);

    if (g_logger.print_to_stderr) {
        fprintf(stderr, "%s", buffer_with_timestamp);
    }
}
