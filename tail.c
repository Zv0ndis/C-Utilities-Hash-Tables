/*
 * Jméno: Tomas Zvonicek
 * Fakulta: Fakulta informačních technologií
 * Příklad: Příklad 1 – tail
 * Datum: 22.4.2025
 */
#include "cbuf.h"
#include <bits/posix2_lim.h>
#include <complex.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int fileno(FILE *stream);

#define LINE_COUNT_BASE 10
#define true 1
#define false 0
#define MAX_LINE_LENGTH 4096
#define ERROR -1

int loadArgs(int argc, char *argv[], int *countOfLines, char **fileName,
             bool *fromStdin) {

    if (!isatty(fileno(stdin))) { // Check if stdin is not a terminal
        struct stat stats;
        fstat(fileno(stdin), &stats);
        *fromStdin = (stats.st_size > 0);
    }

    for (int i = 1; i < argc; i++) { // Start from 1 to skip the program name
        if (!strcmp(argv[i], "-n")) {
            if (i + 1 < argc) {
                // Check if the next argument is a number
                if ((strspn(argv[i + 1], "0123456789") ==
                     strlen(argv[i + 1]))) {
                    // Convert the argument to an integer
                    *countOfLines = atoi(argv[i + 1]);
                    if (*countOfLines < 0) { // Check if the number is negative
                        fprintf(stderr, "Error: Invalid line count\n");
                        return 1;
                    }
                } else { // If not a number, print error
                    fprintf(stderr, "Error: Invalid line count\n");
                    return 1;
                }
                i++;
            } else { // If no argument after -n, print error
                fprintf(stderr, "Error: -n option requires an argument\n");
                return 1;
            }
        } else {
            if (*fileName == NULL) { // If no filename is provided yet
                *fileName = argv[i];
            } else {
                fprintf(stderr, "Error: Multiple filenames provided\n");
                return 1;
            }
        }
    }

    if (!(*fileName == NULL) &&
        *fromStdin) { // If both file and stdin are provided
        fprintf(stderr, "Error: Cannot specify both file and stdin input\n");
        return 1;
    }
    return 0;
}

FILE *fileInit(char *fileName, bool *fromStdin) {
    // Check if filename is provided, if not, read from stdin
    FILE *file;

    if (fileName == NULL) {
        *fromStdin = true;
        file = stdin;
    } else {
        file = fopen(fileName, "r");
        if (file == NULL) {
            fprintf(stderr, "Error: Could not open file %s\n", fileName);
            return NULL;
        }
    }

    if (stdin == NULL) {
        fprintf(stderr, "Error: stdin is not available\n");
        return NULL;
    }

    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", fileName);
        return NULL;
    }

    return file;
}

int main(int argc, char *argv[]) {

    int countOfLines = LINE_COUNT_BASE;
    char *fileName = NULL;
    FILE *file = NULL;
    bool fromStdin = false;

    if (loadArgs(argc, argv, &countOfLines, &fileName, &fromStdin)) {
        return 1;
    }

    if (!countOfLines)
        return 0; // no lines to read nothing to write nothing to create
                  // ¯\_(ツ)_/¯

    file = fileInit(fileName, &fromStdin);
    if (file == NULL) {
        printf("Error: File initialization failed\n");
        return 1;
    }

    cbuf_t *cbf = cbuf_create(countOfLines); // Create circular buffer
    if (cbf == NULL) {
        fprintf(stderr, "Error: Could not create circular buffer\n");
        fclose(file);
        return 1;
    }

    char line[MAX_LINE_LENGTH];         // Buffer
    int truncation_warning_printed = 0; // Flag to check if warning was printed

    while (fgets(line, sizeof(line), file) != NULL) {
        // truncate line from more characters then
        size_t len = strlen(line);
        if (len == MAX_LINE_LENGTH - 1 && line[len - 1] != '\n') {
            if (!truncation_warning_printed) {
                fprintf(
                    stderr,
                    "Warning: Line longer than %d characters was truncated.\n",
                    MAX_LINE_LENGTH - 2);
                truncation_warning_printed = 1;
            }

            // truncation of string
            int ch;
            while ((ch = fgetc(file)) != '\n' && ch != EOF)
                ;
        }

        if (cbuf_put(line, cbf) != 0) {
            fprintf(stderr, "Error: Could not add line to buffer\n");
            cbuf_free(cbf);
            fclose(file);
            return 1;
        }
    }

    int readCount = 0;
    while (readCount < countOfLines) { // Read up to countOfLines
        char *str = cbuf_gets(cbf);
        if (str == NULL) {
            break; // Buffer is empty
        }
        printf("%s", str);
        free(str); // Remember to free
        readCount++;
    }
    // Free the circular buffer
    cbuf_free(cbf);
    fclose(file);
    return 0;
}