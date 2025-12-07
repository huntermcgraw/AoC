#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    FILE *file = fopen("example.txt", "r");
    
    int length = 4096;

    int count = 0;
    unsigned long long sum = 0;
    char matrix[10][length];
    unsigned long long problem[1024];
    unsigned long long sums[1024];

    int num_lines = 0;
    while (fgets(matrix[num_lines], sizeof(matrix[num_lines]), file) != NULL) {
        num_lines++;
        printf("Line %d: %s\n", num_lines, matrix[num_lines - 1]);
    }

    fclose(file);

    int actual_length = strlen(matrix[0]);

    for (int i = actual_length - 1; i >= actual_length - 10; i--) {
        for (int j = 0; j < num_lines; j++) {
            printf("Processing Matrix[%d][%d]: %c\n", j, i, matrix[j][i]);
        }
    }

    printf("Actual length: %d\n", actual_length);

    for (int k = 0; k < actual_length; k++) {
        sum += sums[k];
    }

    printf("Grand total: %llu\n", sum);

    return 0;
}