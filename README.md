# yclog
A simple C log library

## Feature

* Pure C99
* Multiple log level
* Print log to file
* Log rotation ( both file size and file number support to be configured )
* Enable/disable printing log to stderr at the sametime
* Append local timestamp automatically

## Usage

```c
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
    char fname[] = "main()";

    init_log(DEBUG, /*log mask*/
            true, /* print to stderr */
            "default.log", /* log file name */
            10, /* max size (by MB) per file */
            10  /* rotation number */
            );

    print_log(INFO, "%s: Startup ...\n", fname);
    test();
    print_log(INFO, "%s: Shutdown ...\n", fname);

    return 0;
}
```