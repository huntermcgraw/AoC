#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    FILE *file = fopen("input.txt", "r");
    
    int length = 4096;

    int count = 0;
    unsigned long long sum = 0;
    char operator_temp[length];
    char operator[length];

    int num_lines = 0;
    while (fgets(operator_temp, sizeof(operator_temp), file) != NULL) {
        num_lines++;
        printf("Line %d: %s\n", num_lines, operator_temp);
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
    char line[length];
    unsigned long long sums[actual_length + 1];
    for (int i = 0; i < actual_length; i++) {
        if (operator[i] == '*') {
            sums[i] = 1;
        } else {
            sums[i] = 0;
        }
    }

    fseek(file, 0, SEEK_SET);
    printf("Num lines: %d\n", num_lines);
    char *savepointer;

    for (int i = 0; i < num_lines - 1; i++) {
        fgets(line, sizeof(line), file);

        char *token = strtok_r(line, " ", &savepointer);
        
        for (int j = 0; j < actual_length; j++) {
            //printf("Token: %s\n", token);
            if (operator[j] == '+') {
                //printf("Adding %d to sums[%d]\n", atoi(token), j);
                sums[j] += strtoull(token, NULL, 10);
                //printf("sums[%d] is now %d\n", j, sums[j]);
            } else if (operator[j] == '*') {
                //printf("Multiplying %d to sums[%d]\n", atoi(token), j);
                sums[j] *= strtoull(token, NULL, 10);
                //printf("sums[%d] is now %d\n", j, sums[j]);
            }
            token = strtok_r(NULL, " ", &savepointer);
            if (token == NULL) {
                break;
            }
            
        }
        
    }
    for (int k = 0; k < actual_length; k++) {
        printf("Sum for column %d: %llu\n", k, sums[k]);
    }

    fclose(file);

    for (int k = 0; k < actual_length; k++) {
        sum += sums[k];
    }

    printf("Grand total: %llu\n", sum);

    return 0;
}