#include <stdio.h>
#include <stdlib.h>

int main() {
    
    FILE *file = fopen("input.txt", "r");
    
    int sum = 0;
    char line[102]; //17

    while (fgets(line, sizeof(line), file) != NULL) {
        int highest_first_digit = line[0] - '0';
        int highest_digits[102]; //17
        int highest_digit_count = 0;
        highest_digits[highest_digit_count] = 0;
        highest_digit_count++;
        for(int i = 1; i < 99; i++) { //14
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
            for (int j = highest_digits[i] + 1; j < 100; j++) { //15
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
        sum += highest_first_digit * 10 + highest_second_digit;
    }

    fclose(file);
    
    printf("Total output joltage: %d\n", sum);

    return 0;
}