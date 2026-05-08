/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */
#include "htab_private.h"

void htab_free(htab_t *t) {
    if (t == NULL) {
        return; // Invalid input
    }

    htab_clear(t); // Clear the table first
    free(t->buckets); // Free the array of buckets
    free(t); // Free the table itself
}