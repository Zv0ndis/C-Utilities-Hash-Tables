/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */
#include "htab_private.h"


htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    if (t == NULL || key == NULL) {
        return NULL;
    }

    size_t index = htab_hash_function(key) % t->arrSize;
    struct htab_item *item = t->buckets[index];

    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            return &item->pair; // Found the key, return the pair
        }
        item = item->next; // Move to the next item in the linked list
    }

    return NULL; // Key not found
}