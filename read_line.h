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
int read_line(char **s, FILE *fp);
