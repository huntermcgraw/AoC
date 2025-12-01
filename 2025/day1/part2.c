#include <stdio.h>
#include <stdlib.h>

int main() {
    
    FILE *file = fopen("example.txt", "r");
    
    int position = 50;
    int count = 0;
    int value, prev_pos;
    int rotate_right;
    char line[6];

    printf("Current position: %d\n", position);

    while (fgets(line, sizeof(line), file) != NULL) {
        prev_pos = position;
        rotate_right = line[0] == 'R' ? 1 : 0;
        value = atoi(line+1);
        count += (value / 100);
        if (rotate_right) {
            position += value;
        } else {
            position -= value;
        }
        position %= 100;
        if (position < 0) {
            if (position + value != 0 && value < 100)
                count++;
            position += 100;
        } else if (position < prev_pos && rotate_right && position != 0) {
            count++;
        } else if (prev_pos != 0 && position == 0) {
            count++;
        }
        printf("The dial is rotated %s to point at %d.\n", line, position);
        printf("Current count: %d\n\n", count);
    }

    fclose(file);
    
    printf("Password: %d\n", count);

    return 0;
}