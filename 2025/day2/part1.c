#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long check_ids(char *range); // 1845935168 is too low

int main() {
    
    FILE *file = fopen("input.txt", "r");
    
    unsigned long long count = 0;
    char line[1024];
    char *range;
    char *saveptr;

    fgets(line, sizeof(line), file);
    range = strtok_r(line, ",", &saveptr);

    printf("Processing range: %s\n", range);
    count += check_ids(range);

    while (range != NULL) {

        range = strtok_r(NULL, ",", &saveptr);

        if (range == NULL) {
            break;
        }

        printf("Processing range: %s\n", range);
        count += check_ids(range);

    }
    
    fclose(file);
    
    printf("Sum: %llu\n", count);

    return 0;
}

unsigned long long check_ids(char *range) {
    unsigned long long count = 0;
    char *start = strtok(range, "-");
    char *end = strtok(NULL, "-");
    
    for (unsigned long long id = strtoull(start, NULL, 10); id <= strtoull(end, NULL, 10); id++) {

        char id_str[20];
        sprintf(id_str,"%llu", id);

        int num_digits = strlen(id_str);
        int middle_index = num_digits / 2;

        if (num_digits % 2 != 0) {
            continue;
        }

        for (int i = 0; i < middle_index; i++) {
            if (id_str[i] != id_str[middle_index + i]) {
                break;
            }
            if (i == middle_index - 1) {
                count += id;
                //printf("Matching ID: %s\n", id_str);
            }
        }

    }
    
    return count;
}