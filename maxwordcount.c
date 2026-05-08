/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */
 
#include "htab.h"
#include "io.c"

#define MAX 256

unsigned int maxFreq = 0;

void find_maxFrequency(htab_pair_t *data) { // Find the maximum frequency
    if (data->value > maxFreq) {
        maxFreq = data->value;
    }
}

void print_maxFrequency(htab_pair_t *data) { // Print the maximum frequency
    if (data->value == maxFreq) {
        printf("%s\t%d\n", data->key, data->value); // Print the word and its frequency
    }
}

// Usage example
void find_and_print_maxFrequency(const htab_t *table) { // Find and print the maximum frequency


    // find the maximum frequency
    htab_for_each(table, find_maxFrequency);

    // Sprint all entries with the maximum frequency
    htab_for_each(table, print_maxFrequency);
}

int main() {
    htab_t *table = htab_init(19997); // allocate memory for the hash table, it has to be prime because of the hash function 
    if (table == NULL) {
        fprintf(stderr, "Error: Could not initialize hash table\n");
        return 1;
    }

    char word[MAX];
    while (read_word(MAX, word, stdin) > 0) {
        // printf("strlen: %d\n", strlen(word));
        htab_pair_t *pair = htab_lookup_add(table, word);
        if (pair == NULL) {
            fprintf(stderr, "Error: Could not add word to hash table\n");
            htab_free(table);
            return 1;
        }
        pair->value++;
    }

    find_and_print_maxFrequency(table);
    // printf("array size: %zu\n", table->arr_size);

    htab_free(table);
    return 0;
}