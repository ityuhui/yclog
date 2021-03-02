#include <stdio.h>
#include "log.h"

int main()
{
    char fname[] = "main";

    init_log(DEBUG, "local.log", 10, 10);
    print_log(INFO, "%s: Starts up...\n", fname);

    return 0;
}