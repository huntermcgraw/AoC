#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long calc_line(char *line, int line_length);

int main() {
    
    FILE *file = fopen("example.txt", "r");

    char line[102];
    unsigned long long sum = 0;

    fgets(line, sizeof(line), file);
    int line_length = strlen(line);
    printf("Line length: %d\n", line_length);

    sum += calc_line(line, line_length);

    while (fgets(line, sizeof(line), file) != NULL) {
        sum += calc_line(line, line_length);
    }

    fclose(file);
    
    printf("Total output joltage: %llu\n", sum);

    return 0;
}

unsigned long long calc_line(char *line, int line_length) {
    
    int highest[12];
    highest[0] = line[0] - '0';
    for (int i = 1; i < 12; i++) {
        highest[i] = -1;
    }

    int highest_digits[12][line_length];
    int highest_digit_count[12];
    
    for(int k = 12; k > 0; k--) {
        highest_digit_count[12 - k] = 0;
        highest_digits[12 - k][highest_digit_count[12 - k]] = 0;
        highest_digit_count[12 - k]++;
        if (k == 12) {
            for(int i = 1; i < line_length - k; i++) { // line length = 101, so stop before 89 (or line length = 16, stop before 4)
                if (line[i] - '0' > highest[12 - k]) {
                    highest[12 - k] = line[i] - '0';
                    highest_digit_count[12 - k] = 0;
                    highest_digits[12 - k][highest_digit_count[12 - k]] = i;
                    highest_digit_count[12 - k]++;
                } else if (line[i] - '0' == highest[12 - k]) {
                    highest_digits[12 - k][highest_digit_count[12 - k]] = i;
                    highest_digit_count[12 - k]++;
                }
            }
        } else if (k > 1) {
            for (int i = 0; i < highest_digit_count[(12 - k) - 1]; i++) {
                for (int j = highest_digits[(12 - k) - 1][i] + 1; j < line_length - k; j++) {
                    if (line[j] - '0' > highest[12 - k]) {
                    highest[12 - k] = line[j] - '0';
                    highest_digit_count[12 - k] = 0;
                    highest_digits[12 - k][highest_digit_count[12 - k]] = j;
                    highest_digit_count[12 - k]++;
                } else if (line[j] - '0' == highest[12 - k]) {
                    highest_digits[12 - k][highest_digit_count[12 - k]] = j;
                    highest_digit_count[12 - k]++;
                }
                }
            }
        } else {
            for (int i = 0; i < highest_digit_count[(12 - k) - 1]; i++) {
                for (int j = highest_digits[(12 - k) - 1][i] + 1; j < line_length - 1; j++) {
                    if (line[j] == '9') {
                        highest[12 - k] = line[j] - '0';
                        break;
                    } else if (line[j] - '0' > highest[12 - k]) {
                        highest[12 - k] = line[j] - '0';
                    }
                }
                if (highest[12 - k] == 9) {
                    break;
                }
            }
        }
    }
    printf("Line highest digits: ");
    for (int i = 0; i < 12; i++) {
        printf("%d", highest[i]);
    }
    printf("\n");

    return (highest[0] * 10 + highest[1]); // for all 12
}