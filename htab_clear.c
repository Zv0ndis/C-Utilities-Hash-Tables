/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */
#include "htab_private.h"

void htab_clear(htab_t *t) { // Clears the hash table
    if (t == NULL) {
        return; // Invalid input
    }

    for (size_t i = 0; i < t->arrSize; i++) {
        struct htab_item *item = t->buckets[i];
        while (item != NULL) {
            struct htab_item *temp = item;
            item = item->next;            // Move to the next item
            free((char *)temp->pair.key); // Free the duplicated key
            free(temp);                   // Free the item
        }
        t->buckets[i] = NULL; // Set the bucket to NULL after clearing
    }
    t->size = 0; // Reset the size of the table
}
