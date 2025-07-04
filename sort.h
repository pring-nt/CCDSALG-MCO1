/*
GROUP NUMBER : 45
    LASTNAME1, FIRSTNAME1: TRINIDAD, NATHAN         SECTION1: S13
    LASTNAME2, FIRSTNAME2: DIMAUNAHAN, CHELSEA JEI  SECTION2: S14
    LASTNAME3, FIRSTNAME3: SALAMIDA, GABRIEL        SECTION3: S13
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Stack.h"

typedef struct _Points Points;

void findAnchor(Points*, int);
void computePolarAngles(Points*, int);
double distanceSquared(Points, Points);
void selectionSort(Points*, int);
void mergeSort(Points*, int, int);
void merge(Points*, int, int, int);
