#include "fill_area.h"

int main() {
    char filename[256];
    int startRow, startCol;
    int rows, cols;
    struct pixel** image;
    
    printf("Enter image filename: ");
    scanf("%255s", filename);
    
    printf("Enter row and column coordinates: ");
    scanf("%d %d", &startRow, &startCol);
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    fscanf(file, "%d %d", &rows, &cols);
    
    image = (struct pixel**)malloc(rows * sizeof(struct pixel*));
    for (int i = 0; i < rows; i++) {
        image[i] = (struct pixel*)malloc(cols * sizeof(struct pixel));
    }
    
    readImage(file, image, &rows, &cols);
    fclose(file);
    
    fillArea(image, rows, cols, startRow, startCol);
    
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    
    writeImage(file, image, rows, cols);
    fclose(file);
    
    for (int i = 0; i < rows; i++) {
        free(image[i]);
    }
    free(image);
    
    return 0;
} 