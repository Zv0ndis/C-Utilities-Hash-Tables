/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */
 
#ifndef HTAB_PRIVATE_H
#define HTAB_PRIVATE_H

#include <stdio.h>
#include "htab.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

struct htab_item {
    htab_pair_t pair;       // item pair
    struct htab_item *next; // pointer to the next item in the list
};

typedef struct htab_item htab_item;

struct htab {
    size_t size;                // count of items in the table
    size_t arrSize;            // array size
    struct htab_item **buckets; // array of pointers to the first item in each bucket
};

size_t htab_hash_function(htab_key_t str);

#endif // HTAB_PRIVATE_H