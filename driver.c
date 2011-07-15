#include <stdio.h>
#include <stdlib.h>

#include "read_line.h"

/* Simple manual test driver for get_line */
int main(void) {
    char *buff = NULL;

    /* read lines from stdin and print them out to stdout until an 
     * EOF is encountered */
    while (read_line(&buff, stdin) != -1) {
        puts(buff);
        free(buff);
    }
    puts("test driver done");

    return 0;
}
