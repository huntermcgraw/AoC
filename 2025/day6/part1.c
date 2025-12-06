#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    FILE *file = fopen("example.txt", "r");
    
    int length = 512;

    int count = 0;
    int sum = 0;
    char operator_temp[length];
    char operator[length];

    int num_lines = 0;
    while (fgets(operator_temp, sizeof(operator_temp), file) != NULL) {
        num_lines++;
    }
    printf("Total lines read: %d\n", num_lines);

    int actual_length = 0;
    for (int i = 0; i < strlen(operator_temp); i++) {
        if (operator_temp[i] == '*' || operator_temp[i] == '+') {
            operator[actual_length] = operator_temp[i];
            actual_length++;
        }
    }
    printf("Operator: %s\n", operator);

    printf("Operator length: %d\n", actual_length);
    char line[actual_length + 1];
    int sums[actual_length + 1];

    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < num_lines - 1; i++) {
        fgets(line, sizeof(line), file);
        for (int j = 0; j < length; j++) {
            if (i == 0) {
                printf("First number in line %d\n", atoi(strtok(line, " ")));
                sums[j] += atoi(strtok(line, " "));
            } else {
                sums[j] += atoi(strtok(NULL, " "));
            }
            
        }
    }
    for (int k = 0; k < actual_length; k++) {
        printf("Sum for column %d: %d\n", k, sums[k]);
    }

    fclose(file);

    printf("Grand total: %d\n", sum);

    return 0;
}