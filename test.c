#include <stdio.h>
#include "log.h"

int main(int argc, char *argv[])
{
    char fname[] = "main";

    const char *log_file_name = "default.log";
    if (2 == argc && argv[1]) {
        log_file_name = argv[1];
    }
    init_log(DEBUG, true, log_file_name, 10, 10);

    print_log(INFO, "%s: Startup ...\n", fname);
    print_log(WARNING, "%s: Warning ...\n", fname);
    print_log(DEBUG, "%s: Debug ...\n", fname);
    print_log(ERROR, "%s: Error ...\n", fname);
    print_log(INFO, "%s: Shutdown ...\n", fname);

    return 0;
}