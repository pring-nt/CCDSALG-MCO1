#include "sort.h"

/*
    NEED TO DO:
    - find the anchor point (the point with the lowest y-coordinate, and if there are ties, 
      the one with the lowest x-coordinate)
    - sort the points based on polar angle with respect to the anchor point
    - use selection sort to sort the points based on polar angle
*/

void findAnchor(Points points[], int n) {
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[minIndex].y ||
            (points[i].y == points[minIndex].y && points[i].x < points[minIndex].x)) {
            minIndex = i;
        }
    }

    // Swap the anchor point with the first point in the array
    if (minIndex != 0) {
        Points temp = points[0];
        points[0] = points[minIndex];
        points[minIndex] = temp;
    }
}

/*
    The cross product determines the relative orientation of three points:
    - If the result is positive, the points are in counter-clockwise order.
    - If the result is negative, the points are in clockwise order.
    - If the result is zero, the points are collinear.
*/
double crossProduct(Points a, Points b, Points anchor) {
    return (a.x - anchor.x) * (b.y - anchor.y) - (a.y - anchor.y) * (b.x - anchor.x); 
        // I guess this is like final - initial formula but relative to the anchor point
}   

// Used when the points have the same polar angle
double distanceSquared(Points a, Points anchor) {
    double dx = a.x - anchor.x;
    double dy = a.y - anchor.y;
    return dx * dx + dy * dy;
}

// Compare two points based on their polar angle with respect to the anchor point
int comparePolar(Points a, Points b, Points anchor) {
    double cross = crossProduct(a, b, anchor);

    if (cross > 0) {
        return -1; // left turn, a is before b in polar order
    } else if (cross < 0) {
        return 1;  // right turn, b is before a in polar order
    } 
    else 
    {
        // Same polar angle — use distance
        double d1 = distanceSquared(a, anchor);
        double d2 = distanceSquared(b, anchor);

        if (d1 < d2) {
            return -1; // a is closer to anchor
        } else {
            return 1;  // b is closer or same distance
        }
    }
}

void selectionSort(Points points[], int n) {
    Points anchor = points[0]; // The anchor is already the first index

    for (int i = 1; i < n - 1; i++) {   // Start with index 1 since index 0 is the anchor
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (comparePolar(points[j], points[minIndex], anchor) < 0) {
                minIndex = j;
            }
        }

        // Swap the found minimum point with the current point
        if (minIndex != i) {
            Points temp = points[i];
            points[i] = points[minIndex];
            points[minIndex] = temp;
        }
    }
}

