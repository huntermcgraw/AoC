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

    sum += calc_line(line, line_length);

    while (fgets(line, sizeof(line), file) != NULL) {
        sum += calc_line(line, line_length);
    }

    fclose(file);
    
    printf("Total output joltage: %llu\n", sum);

    return 0;
}

unsigned long long calc_line(char *line, int line_length) {
    
    int highest_first_digit = line[0] - '0';
    int highest_digits[line_length];
    int highest_digit_count = 0;
    highest_digits[highest_digit_count] = 0;
    highest_digit_count++;
    for(int i = 1; i < line_length - 2; i++) { 
        if (line[i] - '0' > highest_first_digit) {
            highest_first_digit = line[i] - '0';
            highest_digit_count = 0;
            highest_digits[highest_digit_count] = i;
            highest_digit_count++;
        } else if (line[i] - '0' == highest_first_digit) {
            highest_digits[highest_digit_count] = i;
            highest_digit_count++;
        }
    }
    int highest_second_digit = -1;
    for (int i = 0; i < highest_digit_count; i++) {
        for (int j = highest_digits[i] + 1; j < line_length - 1; j++) {
            if (line[j] == '9') {
                highest_second_digit = line[j] - '0';
                break;
            } else if (line[j] - '0' > highest_second_digit) {
                highest_second_digit = line[j] - '0';
            }
        }
        if (highest_second_digit == 9) {
            break;
        }
    }
    printf("Line highest digits: %d, %d\n", highest_first_digit, highest_second_digit);

    return (highest_first_digit * 10 + highest_second_digit);
}