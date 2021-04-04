# yclog
A simple C log library

## Feature

* Pure C99
* Multiple log level
* Print log to file
* Log file rotation ( both file size and file number support to be configured )
* Enable/disable printing log to stderr at the sametime
* Append local timestamp automatically

## Installation

### Option 1
Copy the files `log.h` and `log.c` into your project directory by manual.

### Option 2
Add `ycloc` as submodule to your project repository, then you can sync up the update of original `yclog` repository.

```shell
cd $your_project_directory
git submodule add https://github.com/ityuhui/yclog.git
``` 


## Usage

```c
#include "log.h"

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
    char *warning_msg = "This is a warning message.";
    print_log(WARNING, "%s: Warning: %s\n", fname, warning_msg);
    print_log(DEBUG, "%s: Debug ...\n", fname);
    print_log(ERROR, "%s: Error ...\n", fname);
    print_log(INFO, "%s: Shutdown ...\n", fname);

    return 0;
}
```
