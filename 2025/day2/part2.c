#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

unsigned long long check_ids(char *range, regex_t regex);

int main() {
    
    FILE *file = fopen("input.txt", "r");
    
    regex_t regex;
    int return_value;
    char* pattern = "^([0-9]+)\\1+$";
    return_value = regcomp(&regex, pattern, REG_EXTENDED);

    unsigned long long count = 0;
    char line[1024];
    char *range;
    char *saveptr;

    fgets(line, sizeof(line), file);
    range = strtok_r(line, ",", &saveptr);

    count += check_ids(range, regex);

    while (range != NULL) {

        range = strtok_r(NULL, ",", &saveptr);

        if (range == NULL) {
            break;
        }

        count += check_ids(range, regex);

    }
    
    fclose(file);
    regfree(&regex);
    
    printf("Sum: %llu\n", count);

    return 0;
}

unsigned long long check_ids(char *range, regex_t regex) {

    int return_value;
    unsigned long long count = 0;
    char *start = strtok(range, "-");
    char *end = strtok(NULL, "-");
    unsigned long long start_num = strtoull(start, NULL, 10);
    unsigned long long end_num = strtoull(end, NULL, 10);
    for (unsigned long long id = start_num; id <= end_num; id++) {

        char id_str[20];
        sprintf(id_str,"%llu", id);

        int num_digits = strlen(id_str);
        int middle_index = num_digits / 2;

        //printf("Checking ID: %s\n", id_str);
        return_value = regexec(&regex, id_str, 0, NULL, 0);

        if (!return_value) {
            count += id;
            printf("Matching ID: %s\n", id_str);
        }

    }
    
    return count;
}