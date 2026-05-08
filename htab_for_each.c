/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */
#include "htab_private.h"


void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    if (t == NULL || f == NULL) {
        return;
    }
    
    // Iterate through all buckets
    for (size_t i = 0; i < htab_bucket_count(t); i++) {
        // Iterate through all items in the current bucket
        for (htab_item *item = t->buckets[i]; item != NULL; item = item->next) {
            // Call the callback function for each item
            f(&(item->pair));
        }
    }
}