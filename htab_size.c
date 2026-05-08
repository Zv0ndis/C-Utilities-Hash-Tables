/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */
 
#include "htab_private.h"

size_t htab_size(const htab_t *t) { // Returns the number of elements in the hash table
    if (t == NULL) {
        fprintf(stderr, "Error: htab_size called with NULL pointer\n");
        return 0;
    }
    size_t size = t->size;
    return size;
}