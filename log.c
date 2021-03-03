#include "log.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILE_NAME_MAX_LENGTH 128
#define VL_BUFFER_SIZE 1024
#define MBytes (1024*1024)
#define DEFAULT_LOG_LEVEL INFO

typedef struct logger_t {
    log_level log_mask;
    char *log_file;
    unsigned long max_size_by_Mbytes_per_file;
    int max_rotate_number;
    bool print_to_stderr;
} logger;

static logger g_logger;
static pthread_mutex_t logger_mutex;

static char *log_level_to_string(log_level level)
{
    char *levels[] = { "", "DEBUG", "INFO", "WARNING", "ERROR" };
    return levels[level];
}

static void get_current_time(char *buffer, int buffer_size)
{
    char *wday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep);
    snprintf(buffer, buffer_size, "%d-%02d-%02d %s %02d:%02d:%02d", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
}

static unsigned long get_file_size(const char *file_name)
{
    struct stat buf;
    if (stat(file_name, &buf) < 0) {
        return 0;
    }
    return (unsigned long) buf.st_size;
}

static bool does_file_exist(const char *file_name)
{
    if ((access(file_name, F_OK)) != -1) {
        return true;
    } else {
        return false;
    }
}

static void rotate_log_files()
{
    char old_file_name[FILE_NAME_MAX_LENGTH];
    char new_file_name[FILE_NAME_MAX_LENGTH];

    for (int i = g_logger.max_rotate_number; i > 0; i--) {
        snprintf(old_file_name, sizeof(old_file_name), "%s.%d", g_logger.log_file, i - 1);
        if (does_file_exist(old_file_name)) {
            snprintf(new_file_name, sizeof(new_file_name), "%s.%d", g_logger.log_file, i);
            rename(old_file_name, new_file_name);
        }
    }

    snprintf(new_file_name, sizeof(new_file_name), "%s.1", g_logger.log_file);
    rename(g_logger.log_file, new_file_name);
}

void init_log(log_level log_mask, bool print_to_stderr, const char *log_file_name, int max_size_by_Mbytes_per_file, int max_rotate_number)
{
    pthread_mutex_lock(&logger_mutex);

    if (log_mask < DEBUG || log_mask > ERROR) {
        g_logger.log_mask = DEFAULT_LOG_LEVEL;
    } else {
        g_logger.log_mask = log_mask;
    }

    g_logger.print_to_stderr = print_to_stderr;
    g_logger.log_file = strdup(log_file_name);
    g_logger.max_size_by_Mbytes_per_file = max_size_by_Mbytes_per_file;
    g_logger.max_rotate_number = max_rotate_number;

    pthread_mutex_unlock(&logger_mutex);
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
    snprintf(buffer_with_timestamp, sizeof(buffer_with_timestamp), "%s [%s] %s", buffer_timestamp, log_level_to_string(lvl), buffer);

    pthread_mutex_lock(&logger_mutex);

    if (get_file_size(g_logger.log_file) > g_logger.max_size_by_Mbytes_per_file * MBytes) {
        rotate_log_files();
    }

    FILE *fp = fopen(g_logger.log_file, "a");
    fprintf(fp, "%s", buffer_with_timestamp);
    fclose(fp);

    pthread_mutex_unlock(&logger_mutex);

    if (g_logger.print_to_stderr) {
        fprintf(stderr, "%s", buffer_with_timestamp);
    }
}
