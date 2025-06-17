#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BLOCKS 2
#define LINES_PER_BLOCK 11
#define MAX_NUMBERS_PER_LINE 10

typedef struct {
    int numbers[MAX_NUMBERS_PER_LINE];
    int count;
    int has_asterisk;
} LineData;

typedef struct {
    LineData lines[LINES_PER_BLOCK];
} Block;

int main() {
    Block blocks[MAX_BLOCKS];

    for (int block_idx = 0; block_idx < MAX_BLOCKS; block_idx++) {
        for (int line_idx = 0; line_idx < LINES_PER_BLOCK; line_idx++) {
            char buffer[256];
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                fprintf(stderr, "Error reading input. Not enough lines.\n");
                return 1;
            }

            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[--len] = '\0';
            }

            int has_asterisk = 0;
            if (len > 0 && buffer[len - 1] == '*') {
                has_asterisk = 1;
                buffer[--len] = '\0';
            }

            if (line_idx == 0 && buffer[0] == '[') {
                memmove(buffer, buffer + 1, len);
                len--;
            }

            if (line_idx == LINES_PER_BLOCK - 1) {
                if (len > 0 && buffer[len - 1] == ']') {
                    buffer[--len] = '\0';
                }
            }

            LineData* lineData = &blocks[block_idx].lines[line_idx];
            lineData->has_asterisk = has_asterisk;
            lineData->count = 0;

            char* token = strtok(buffer, ",");
            while (token != NULL) {
                if (lineData->count >= MAX_NUMBERS_PER_LINE) {
                    break;
                }
                lineData->numbers[lineData->count] = atoi(token);
                lineData->count++;
                token = strtok(NULL, ",");
            }
        }
    }

    for (int block_idx = 0; block_idx < MAX_BLOCKS; block_idx++) {
        printf("Block %d:\n", block_idx + 1);
        for (int line_idx = 0; line_idx < LINES_PER_BLOCK; line_idx++) {
            LineData* line = &blocks[block_idx].lines[line_idx];
            printf("  Line %2d: ", line_idx + 1);
            for (int i = 0; i < line->count; i++) {
                printf("%d", line->numbers[i]);
                if (i < line->count - 1) {
                    printf(", ");
                }
            }
            if (line->has_asterisk) {
                printf("*");
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}