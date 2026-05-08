/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */
#include "htab_private.h"

bool htab_erase(htab_t *t, htab_key_t key) {
    if (t == NULL || key == NULL) {
        return false; // Invalid input
    }

    size_t index = htab_hash_function(key) % t->arrSize;
    struct htab_item *item = t->buckets[index];
    struct htab_item *prev = NULL;

   
    while (item != NULL) {  // Search for the key in the linked list
        if (strcmp(item->pair.key, key) == 0) { // Key found

            if (prev == NULL) {
                // Removing the first item in the bucket
                t->buckets[index] = item->next;
            } else {
                prev->next = item->next; // Bypass the current item
            }
            free((char *)item->pair.key); // Free the duplicated key
            free(item);                   // Free the item
            t->size--;                    // Decrement the size of the table
            return true;                  // Successfully removed
        }
        prev = item;       // Move to the next item
        item = item->next; // Move to the next item in the linked list
    }
    return false; // Key not found
}