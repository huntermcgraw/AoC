#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    FILE *file = fopen("input.txt", "r");
    
    int num_lines = 200;
    int length = 50;

    int sum = 0;
    char ranges[num_lines][length];
    unsigned long long range_starts[num_lines];
    unsigned long long range_ends[num_lines];
    char line[length];
    char *start;
    char *end;
    unsigned long long id_value;

    int i = 0;
    while (fgets(ranges[i], sizeof(ranges[i]), file) != NULL) {
        if (ranges[i][0] == '\n') {
            break;
        }
        printf("Range: %s", ranges[i]);
        start = strtok(ranges[i], "-");
        end = strtok(NULL, "-");
        range_starts[i] = strtol(start, NULL, 10);
        range_ends[i] = strtol(end, NULL, 10);
        i++;
    }

    int j = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("ID: %s", line);
        for (int k = 0; k < i; k++) {
            id_value = strtoull(line, NULL, 10);
            if (id_value >= range_starts[k] && id_value <= range_ends[k]) {
                sum++;
                break;
            }
        }
        j++;
    }

    fclose(file);
    
    printf("Fresh ingredient IDs: %d\n", sum);

    return 0;
}