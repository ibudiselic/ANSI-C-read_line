/* Author: Ivan Budiselic (ivan.budiselic@gmail.com)
 * Version: 1.1
 * Last Modified: 11.04.2009
 * License: http://www.opensource.org/licenses/bsd-license.php
 * Basically, you are free to use the code as is or modified for whatever purpose,
 * provided you include the above header and the same license. The code is provided 
 * "as is" without any express or implied warranties.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ALLOC_INCREMENT 1024 

int read_line(char **s, FILE *fp) {
    /*
     * Reads a line into *s from the specified file pointer and grows the buffer 
     * accordingly. The user must eventually free the memory when he is done with 
     * the string. Reallocates memory in ALLOC_INCREMENT chunks. The buffer is 
     * terminated with a '\0' character, and doesn't include '\n'. Might allocate 
     * as much as ALLOC_INCREMENT-1 bytes more then necessary to hold the line. 
     * Possibly wrap in a helper function to realloc() to the actual line size.
     * Assumes the buffer is initially empty (memory leak otherwise).
     *
     * Returns -1 if there is a read error or EOF is found, otherwise returns 
     * the number of read characters (the '\0' is not counted).
     */
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

/* simple test driver */
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

