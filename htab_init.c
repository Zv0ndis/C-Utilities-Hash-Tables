/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */
#include "htab_private.h"
#include <limits.h>

htab_t *htab_init(size_t n) {
    if (n == 0) {
        return NULL;
    }

    htab_t *table = malloc(sizeof(htab_t)); // Allocate memory for the table
    if (table == NULL) {
        return NULL;
    }

    table->size = 0;
    table->arrSize = n;
    table->buckets = malloc(n * sizeof(struct htab_item *)); // Allocate memory for the buckets
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }

    for (size_t i = 0; i < n; i++) { 
        table->buckets[i] = NULL;
    }

    return table;
}