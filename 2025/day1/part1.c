#include <stdio.h>
#include <stdlib.h>

int main() {
    
    FILE *file = fopen("input.txt", "r");
    
    int position = 50;
    int count = 0;
    int value;
    int rotate_right;
    char line[6];

    printf("Current position: %d\n", position);

    while (fgets(line, sizeof(line), file) != NULL) {
        rotate_right = line[0] == 'R' ? 1 : 0;
        value = atoi(line+1);
        if (rotate_right) {
            position += value;
        } else {
            position -= value;
        }
        position %= 100;
        if (position < 0) {
            position += 100;
        } else if (position == 0) {
            count++;
        }
        printf("Current position: %d\n", position);
    }

    fclose(file);
    
    printf("Password: %d\n", count);

    return 0;
}