#include "log.h"

void test()
{
    char fname[] = "test()";

    print_log(WARNING, "%s: Warning ...\n", fname);
    print_log(DEBUG, "%s: Debug ...\n", fname);
    print_log(ERROR, "%s: Error ...\n", fname);
}

int main(int argc, char *argv[])
{
    char fname[] = "main";

    const char *log_file_name = "default.log";
    if (2 == argc && argv[1]) {
        log_file_name = argv[1];
    }
    init_log(DEBUG, true, log_file_name, 10, 10);

    for (int i = 0; i < 50; i++) {
        print_log(INFO, "%s: Startup ...\n", fname);
        test();
        print_log(INFO, "%s: Shutdown ...\n", fname);
    }

    return 0;
}
