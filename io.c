/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 2 – maxwordcount
 * Datum: 22.4.2025
 */

#include "htab_private.h"
#include <ctype.h>

int read_word(unsigned max, char s[max], FILE *f) {
    unsigned int i = 0;
    char c;

    // Skip whitespace
    while ((c = fgetc(f)) != EOF && isspace(c)); 

    if (c == EOF) { return EOF; } // End of file

    s[i++] = c; // Store the first character

    while (i < max - 1 && (c = fgetc(f)) != EOF && !isspace(c)) { // Read until whitespace or EOF
        s[i++] = c;
    }

    s[i++] = '\0'; // Null-terminate the string

    if (i == max && c != EOF && !isspace(c)) { // If the word is too long
        bool firstWarning = false;
        while ((c = fgetc(f)) != EOF && !isspace(c)) { // Skip the rest of the word
            if (!firstWarning) {
                firstWarning = true;
                fprintf(stderr,
                        "Warning: Word too long, truncating to %u characters\n",
                        max - 1);
            }
        }
    }

    return i;
}