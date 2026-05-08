/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */
#include "htab_private.h"

size_t htab_bucket_count(const htab_t *t) { // Returns the number of buckets in the hash table
    if (t == NULL) {
        fprintf(stderr, "Error: htab_bucket_count called with NULL pointer\n");
        return 0;
    }
    size_t bucketCount = t->arrSize;
    return bucketCount;
}