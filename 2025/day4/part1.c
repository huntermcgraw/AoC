#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    FILE *file = fopen("input.txt", "r");
    
    int length = 140; // 10, 140

    int count = 0;
    int num_rolls = 0;
    char matrix[length][length + 2]; // +2 for newline and null terminator

    int i = 0;
    while (fgets(matrix[i], sizeof(matrix[i]), file) != NULL) {
        i++;
    }

    fclose(file);
    
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    int prev_num_rolls = 0;
    while(1) {
        prev_num_rolls = num_rolls;
        for (int i = 0; i < length; i++) {
            if (i == 0) {
                for (int j = 0; j < length; j++) {
                    if (matrix[i][j] != '@') {
                        continue;
                    }
                    for (int k = -1; k < 2; k++) {
                        if (matrix[i][j + k] == '@') {
                            count++;
                            //printf("Found at (%d, %d)\n", i, j + k);
                        }
                        if (matrix[i + 1][j + k] == '@') {
                            count++;
                            //printf("Found at (%d, %d)\n", i + 1, j + k);
                        }
                    }
                    //printf("Count at (%d, %d): %d\n", i, j, count);
                    if (count < 5) { // 5 because it counts itself
                        num_rolls++;
                        matrix[i][j] = 'x';
                    }
                    
                    count = 0;
                }
            } else if (i < length - 1) {
                for (int j = 0; j < length; j++) {
                    if (matrix[i][j] != '@') {
                        continue;
                    }
                    for (int k = -1; k < 2; k++) {
                        if (matrix[i - 1][j + k] == '@') {
                            count++;
                        }
                        if (matrix[i][j + k] == '@') {
                            count++;
                        }
                        if (matrix[i + 1][j + k] == '@') {
                            count++;
                        }
                    }
                    //printf("Count at (%d, %d): %d\n", i, j, count);
                    if (count < 5) {
                        num_rolls++;
                        matrix[i][j] = 'x';
                    }
                    count = 0;
                }
            } else {
                for (int j = 0; j < length; j++) {
                    if (matrix[i][j] != '@') {
                        continue;
                    }
                    for (int k = -1; k < 2; k++) {
                        if (matrix[i - 1][j + k] == '@') {
                            count++;
                            //printf("Found at (%d, %d)\n", i - 1, j + k);
                        }
                        if (matrix[i][j + k] == '@') {
                            count++;
                            //printf("Found at (%d, %d)\n", i, j + k);
                        }
                    }
                    //printf("Count at (%d, %d): %d\n", i, j, count);
                    if (count < 5) {
                        num_rolls++;
                        matrix[i][j] = 'x';
                    }
                    count = 0;
                }
            }  
        }
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                if (matrix[i][j] == 'x') {
                    matrix[i][j] = '.';
                }
            }
        }
        if (num_rolls == prev_num_rolls) {
            break;
        }
    }

    printf("Rolls: %d\n", num_rolls);

    return 0;
}