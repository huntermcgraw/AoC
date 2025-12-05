#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    FILE *file = fopen("input.txt", "r"); // 369318224397456 too high / not 366558057869922 / not 346641541043583
                                          // not 361781042408824 // not 357298787457794 // 357298787457794
    
    int num_lines = 200;
    int length = 50;

    unsigned long long sum = 0;
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
        range_starts[i] = strtoull(start, NULL, 10);
        range_ends[i] = strtoull(end, NULL, 10);
        i++;
    }

    // sort ranges by lowest start value
    unsigned long long temp_start;
    unsigned long long temp_end;
    for (int k = 0; k < i - 1; k++) {
        for (int j = 0; j < i - k - 1; j++) {
            if (range_starts[j] > range_starts[j + 1]) {
                unsigned long long temp_start = range_starts[j];
                unsigned long long temp_end = range_ends[j];
                range_starts[j] = range_starts[j + 1];
                range_ends[j] = range_ends[j + 1];
                range_starts[j + 1] = temp_start;
                range_ends[j + 1] = temp_end;
            }
        }
    }

    int current_end;
    int start_temp;
    int k = 0;
    while (k < i) {
        current_end = k;
        start_temp = k;
        for (int j = k + 1; j < i; j++) {
            printf("Current start: %llu, Current end: %llu, Checking against range %llu\n", range_starts[start_temp], range_ends[current_end], range_starts[j]);
            if (range_ends[current_end] >= range_starts[j]) {
                printf("Merging ranges %llu-%llu and %llu-%llu\n", range_starts[start_temp], range_ends[start_temp], range_starts[j], range_ends[j]);
                if (range_ends[j] >= range_ends[current_end]) {
                    current_end = j;
                }
                start_temp += 1;
            } else {
                break;
            }
        }
        
        printf("Adding range %llu-%llu to sum\n", range_starts[k], range_ends[current_end]);
        sum += range_ends[current_end] - range_starts[k] + 1;
        
        k = start_temp + 1;
        
    }

    fclose(file);
    
    printf("Fresh ingredient IDs: %llu\n", sum);

    return 0;
}