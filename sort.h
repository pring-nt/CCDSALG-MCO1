#include <stdio.h>
#include <stdlib.h>

struct _Points {
    double x;
    double y;
};

typedef struct _Points Points;

void findAnchor(Points points[], int n);
double crossProduct(Points a, Points b, Points anchor);
double distanceSquared(Points a, Points anchor);
int comparePolar(Points a, Points b, Points anchor);
void selectionSort(Points points[], int n);
