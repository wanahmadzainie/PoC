#include <stdio.h>
#include <string.h>
#include <ctype.h>


int read_header_line(FILE* fp, char* line, size_t size) {

    
    if (fgets(line, sizeof(line), fp) == NULL) {
        printf("File is empty.\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
        len--;
    }

    int numbers[100];
    int count = 0;
    int offset = 0;
    int num;
    int n;

    while (offset < len) {
        if (sscanf(line + offset, "%d%n", &num, &n) != 1) {
            break;
        }
        numbers[count] = num;
        count++;
        offset += n;

        int found_bracket = 0;
        while (offset < len) {
            if (line[offset] == ']') {
                found_bracket = 1;
                offset++;
                break;
            }
            else if (line[offset] == ',' || isspace(line[offset])) {
                offset++;
            }
            else {
                break;
            }
        }
        if (found_bracket) {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%d\n", numbers[i]);
    }
}

//int main() {
//    FILE* fp = fopen("MatrixSample.txt", "r");
// 
// char line[1000];
//    if (fp == NULL) {
//        perror("Error opening file");
//        return 1;
//    }
//
//
//
//    return 0;
//}