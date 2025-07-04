/*
GROUP NUMBER : 45
    LASTNAME1, FIRSTNAME1: TRINIDAD, NATHAN         SECTION1: S13
    LASTNAME2, FIRSTNAME2: DIMAUNAHAN, CHELSEA JEI  SECTION2: S14
    LASTNAME3, FIRSTNAME3: SALAMIDA, GABRIEL        SECTION3: S13
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct _Points {
    double x;
    double y;
    double polarAngle;
};

typedef struct _Points Points;

void findAnchor(Points points[], int n);
double crossProduct(Points a, Points b, Points anchor);
void computePolarAngles(Points points[], int n, Points anchor);
double distanceSquared(Points a, Points anchor);
void selectionSort(Points points[], int n);
void mergeSort(Points points[], int left, int right);
void merge(Points points[], int l, int m, int r);
