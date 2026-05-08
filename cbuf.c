/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 1 – tail
 * Datum: 22.4.2025
 */

#include "cbuf.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *strdup(const char *s) {
    size_t len = strlen(s);
    char *copy = malloc(len + 1); // +1 for '\0'

    if (copy) {
        memcpy(copy, s, len + 1); // with '\0'
    }
    else if (copy == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }

    return copy;
}

cbuf_t *cbuf_create(int size) {
    cbuf_t *cbuf = malloc(sizeof(cbuf_t));
    if (cbuf == NULL) {
        return NULL;
    }

    cbuf->data = malloc(size * sizeof(char *));
    if (cbuf->data == NULL) {
        free(cbuf);
        return NULL;
    }

    cbuf->size = size;
    cbuf->readIndex = 0;
    cbuf->writeIndex = 0;
    cbuf->isFull = false;

    return cbuf;
}

int cbuf_put(char *string, cbuf_t *cbuf) {

    if (cbuf->writeIndex == cbuf->readIndex && cbuf->isFull) { // Buffer is full
        if (cbuf->data[cbuf->writeIndex] != NULL) { // Free the oldest string
            free(cbuf->data[cbuf->writeIndex]);
            cbuf->data[cbuf->writeIndex] = NULL;
        }
        cbuf->readIndex = (cbuf->readIndex + 1) % cbuf->size; // Move read index
    }

    cbuf->data[cbuf->writeIndex] = strdup(string); // Duplicate the string
    if (cbuf->data[cbuf->writeIndex] == NULL) { // Check for memory allocation failure
        return -1;
    }

    cbuf->writeIndex = (cbuf->writeIndex + 1) % cbuf->size; // Move write index
    cbuf->isFull = (cbuf->writeIndex == cbuf->readIndex); // Check if buffer is full
    return 0;
}

char *cbuf_gets(cbuf_t *cbuf) {
    if (cbuf->readIndex == cbuf->writeIndex && !cbuf->isFull) { // Buffer is empty
        return NULL;
    }

    char *string = strdup(cbuf->data[cbuf->readIndex]); // Duplicate the string
    if (!string) {
        return NULL;
    }

    free(cbuf->data[cbuf->readIndex]); // Free the string in the buffer
    cbuf->data[cbuf->readIndex] = NULL;

    cbuf->readIndex = (cbuf->readIndex + 1) % cbuf->size; // Move read index
    cbuf->isFull = false; // Buffer is not full anymore

    return string;
}

int cbuf_free(cbuf_t *cbuf) { // Free the circular buffer
    if (cbuf == NULL) {
        return 0;
    }

    for (int i = 0; i < cbuf->size; i++) {
        if (cbuf->data[i] != NULL) {
            free(cbuf->data[i]);
            cbuf->data[i] = NULL;
        }
    }

    free(cbuf->data);
    cbuf->data = NULL;

    free(cbuf);
    return 0;
}
