#ifndef FILL_AREA_H
#define FILL_AREA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct pixel {
    char R;
    char G;
    char B;
};

void readImage(FILE* file, struct pixel** image, int* rows, int* cols);
void fillArea(struct pixel** image, int rows, int cols, int startRow, int startCol);
void writeImage(FILE* file, struct pixel** image, int rows, int cols);
double getAverageIntensity(struct pixel p);
int shouldFill(struct pixel p1, struct pixel p2);

#endif