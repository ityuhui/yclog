#include "log.h"

void test()
{
    char fname[] = "test()";

    print_log(CL_WARNING, "%s: Warning ...\n", fname);
    print_log(CL_DEBUG, "%s: Debug ...\n", fname);
    print_log(CL_ERROR, "%s: Error ...\n", fname);
}

int main(int argc, char *argv[])
{
    char fname[] = "main";

    const char *log_file_name = "default.log";
    if (2 == argc && argv[1]) {
        log_file_name = argv[1];
    }
    init_log(CL_DEBUG, true, log_file_name, 10, 10);

    for (int i = 0; i < 50; i++) {
        print_log(CL_INFO, "%s: Startup ...\n", fname);
        test();
        print_log(CL_INFO, "%s: Shutdown ...\n", fname);
    }

    return 0;
}
