/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 1 – tail
 * Datum: 22.4.2025
 */

#ifndef CBUF_H
#define CBUF_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    char **data;       // array of strings
    size_t size;       // max number of elements
    size_t readIndex;  // read pointer
    size_t writeIndex; // write pointer
    bool isFull;      // full flag
} cbuf_t;

// Initialize buffer with given capacity
cbuf_t *cbuf_create(int size);

// Free all memory used by the buffer
int cbuf_free(cbuf_t *cbuf);

// Add a new string to the buffer (makes a copy)
int cbuf_put(char *str, cbuf_t *cbuf);

// Remove and return the oldest string (caller must free)
char *cbuf_gets(cbuf_t *cbuf);

#endif // CBUF_H