#include "fill_area.h"

double getAverageIntensity(struct pixel p) {
    return (p.R + p.G + p.B) / 3.0;
}

int shouldFill(struct pixel p1, struct pixel p2) {
    double intensity1 = getAverageIntensity(p1);
    double intensity2 = getAverageIntensity(p2);
    return fabs(intensity1 - intensity2) <= 1.0;
}

void readImage(FILE* file, struct pixel** image, int* rows, int* cols) {
    int r, g, b;
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%d:%d:%d", &r, &g, &b);
            image[i][j].R = (char)r;
            image[i][j].G = (char)g;
            image[i][j].B = (char)b;
        }
    }
}

void writeImage(FILE* file, struct pixel** image, int rows, int cols) {
    fprintf(file, "%d %d\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d:%d:%d", 
                (unsigned char)image[i][j].R,
                (unsigned char)image[i][j].G,
                (unsigned char)image[i][j].B);
            if (j < cols - 1) fprintf(file, " ");
        }
        fprintf(file, "\n");
    }
}

void fillArea(struct pixel** image, int rows, int cols, int startRow, int startCol) {
    if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols) {
        return;
    }
    
    struct pixel startPixel = image[startRow][startCol];
    
    int** visited = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        visited[i] = (int*)calloc(cols, sizeof(int));
    }
    
    int* stack = (int*)malloc(rows * cols * 2 * sizeof(int));
    int stackSize = 0;
    
    stack[stackSize++] = startRow;
    stack[stackSize++] = startCol;
    
    while (stackSize > 0) {

        int col = stack[--stackSize];
        int row = stack[--stackSize];
        
        if (visited[row][col]) continue;
        visited[row][col] = 1;
        
        image[row][col].R = 0;
        image[row][col].G = 0;
        image[row][col].B = 0;
        
        int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        for (int i = 0; i < 4; i++) {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];
            
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                !visited[newRow][newCol] && 
                shouldFill(startPixel, image[newRow][newCol])) {
                stack[stackSize++] = newRow;
                stack[stackSize++] = newCol;
            }
        }
    }
    
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);
    free(stack);
}
