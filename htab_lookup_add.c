/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */
 
#include "htab_private.h"

char *strdup(const char *s) {
    size_t len = strlen(s);
    char *copy = malloc(len + 1); // +1 for '\0'
    if (copy) {
        memcpy(copy, s, len);
        copy[len] = '\0'; // null-terminate
    }
    return copy;
}

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    if (t == NULL || key == NULL) {
        return NULL;
    }

    size_t index = htab_hash_function(key) % t->arrSize;
    struct htab_item *item = t->buckets[index];

    // Search for the key in the linked list
    while (item != NULL) {
        if (strcmp(item->pair.key, key) == 0) {
            return &item->pair; // Key found, return the pair
        }
        item = item->next; // Move to the next item in the linked list
    }

    // Key not found, create a new item
    struct htab_item *newItem = malloc(sizeof(struct htab_item));
    if (newItem == NULL) {
        return NULL; // Memory allocation failed
    }

    newItem->pair.key = strdup(key); // Duplicate the key string
    if (newItem->pair.key == NULL) {
        free(newItem);
        return NULL; // Memory allocation failed
    }

    newItem->pair.value = 0; // Initialize value to 1
    newItem->next = t->buckets[index]; // Insert at the beginning of the list
    t->buckets[index] = newItem; // Update the bucket

    t->size++; // Increment the size of the table

    return &newItem->pair; // Return the newly created pair
}