#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "read_line.h"

#define ALLOC_INCREMENT 1024 

int read_line(char **s, FILE *fp) {
    char *t=NULL, *p=NULL;
    int c; /* character buffer */
    int len = 0; /* current number of elements read and stored */
    int allocated = 0; /* number of allocated bytes in p */

    p = malloc(ALLOC_INCREMENT);
    if (p == NULL) {
        return -1;
    }
    allocated = ALLOC_INCREMENT;

    /* get next character from file */
    while ((c = fgetc(fp))!=EOF && c!='\n') {
        if (len == allocated) { /* buffer is full, must extend */
            t = realloc(p, allocated + ALLOC_INCREMENT);
            if (t == NULL) {
                free(p);
                return -1;
            }

            p = t;
            allocated += ALLOC_INCREMENT;
        }
        p[len++] = (char)c;
    }
    if (len == 0) {
        if (c == EOF) { /* empty file or read error */
            free(p);
            return -1;
        } else { /* empty line */
            assert(c == '\n');
            p[0] = '\0';
            *s = p;
            return 0;
        }
    }

    if (len+1 != allocated) { /* no room for '\0' */
        t = realloc(p, len+1);
        if (t == NULL) {
            free(p);
            return -1;
        }
        p = t;
    }

    p[len] = '\0';
    *s = p;

    return len;
}
