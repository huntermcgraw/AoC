#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    FILE *file = fopen("input.txt", "r");
    
    int num_lines = 500;

    char line[20];
    int tile_locations[num_lines][2];
    char *start;
    char *end;

    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        start = strtok(line, ",");
        end = strtok(NULL, ",");
        tile_locations[i][0] = strtol(start, NULL, 10);
        tile_locations[i][1] = strtol(end, NULL, 10);
        i++;
    }

    unsigned long long curr_area = 0;
    unsigned long long max_area = 0;
    unsigned long long abs_x = 0;
    unsigned long long abs_y = 0;
    for (int j = 0; j < i; j++) {
        printf("%d,%d\n", tile_locations[j][0], tile_locations[j][1]);
        for (int k = j + 1; k < i; k++) {
            abs_x = abs(tile_locations[j][0] - tile_locations[k][0]);
            abs_y = abs(tile_locations[j][1] - tile_locations[k][1]);
            //printf("C=abs_x=%d, abs_y=%d\n", abs_x, abs_y);
            curr_area = (abs_x + 1) * (abs_y + 1);
            //printf("Area between (%d,%d) and (%d,%d): %lld\n", tile_locations[j][0], tile_locations[j][1], tile_locations[k][0], tile_locations[k][1], curr_area);
            if (curr_area > max_area) {
                printf("New max area found between (%d,%d) and (%d,%d): %llu\n", tile_locations[j][0], tile_locations[j][1], tile_locations[k][0], tile_locations[k][1], curr_area);
                max_area = curr_area;
            }
        }
    }

    fclose(file);
    
    printf("Largest area: %llu\n", max_area);

    return 0;
}