#include "log.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define VL_BUFFER_SIZE 1024

typedef struct logger_t {
    log_level log_mask;
    char *log_file;
    int max_size_by_Mbytes_per_file;
    int max_rotate_number;
} logger;

static logger g_loger;

static void rotate_log_file()
{

}

void init_log(log_level log_mask, const char *log_file_name, int max_size_by_Mbytes_per_file, int max_rotate_number)
{
    g_loger.log_mask = log_mask;
    g_loger.log_file = strdup(log_file_name);
    g_loger.max_size_by_Mbytes_per_file = max_size_by_Mbytes_per_file;
    g_loger.max_rotate_number = max_rotate_number;
}

void print_log(log_level lvl, char *fmt, ...)
{
    if (lvl < g_loger.log_mask) {
        return;
    }

    char buffer[VL_BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    va_list vl;
    va_start(vl, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, vl);
    va_end(vl);

    rotate_log_file();

    FILE *fp = fopen(g_loger.log_file, "a");
    fprintf(fp, "%s", buffer);
    fclose(fp);
}

