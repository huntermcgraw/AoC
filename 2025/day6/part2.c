#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
    
    FILE *file = fopen("input.txt", "r");
    
    int length = 4096;
    unsigned long long sum = 0;
    char matrix[10][length];

    int num_lines = 0;
    while (fgets(matrix[num_lines], sizeof(matrix[num_lines]), file) != NULL) {
        num_lines++;
        printf("Line %d: %s\n", num_lines, matrix[num_lines - 1]);
    }

    fclose(file);

    int actual_length = strlen(matrix[0]);

    unsigned long long problem[1024][num_lines];
    unsigned long long sums[1024];

    memset(problem, 0, sizeof(problem));

    int count;
    int operations = 0;
    int problem_finished = 0;
    int num_numbers = 0;
    for (int i = actual_length - 1; i >= 0; i--) {
        count = 0;
        for (int j = 0; j < num_lines; j++) {
            if (matrix[j][i] == ' ' || matrix[j][i] == '\n' || matrix[j][i] == '\0') {
                if (j != num_lines - 1)
                if (count != 0) {
                    count /= 10;
                }
            } else if (matrix[j][i] == '+') {
                problem[operations][0] = 0;
                problem_finished = 1;
            } else if (matrix[j][i] == '*') {
                problem[operations][0] = 1;
                problem_finished = 1;
            } else {
                count += (matrix[j][i] - '0') * pow(10, num_lines - 2 - j);
            }
        }
        if (count != 0) {
            problem[operations][num_numbers + 1] = count;
            num_numbers++;
            if (problem_finished) {
                num_numbers = 0;
                operations++;
                problem_finished = 0;
            }
        }
    }

    printf("operations: %d\n", operations);

    for (int i = 0; i < operations; i++) {
        sums[i] = problem[i][0];
    }

    for (int i = 0; i < operations; i++) {
        for (int j = 1; j < num_lines; j++) {
            printf("%llu ", problem[i][j]);
            if (problem[i][0]) {
                if (problem[i][j] == 0) continue;
                sums[i] *= problem[i][j];
            } else {
                sums[i] += problem[i][j];
            }
        }
        printf("\n");
    }

    for (int i = 0; i < operations; i++) {
        sum += sums[i];
        printf("Subtotal %d: %llu\n", i + 1, sums[i]);
    }

    printf("Grand total: %llu\n", sum);

    return 0;
}