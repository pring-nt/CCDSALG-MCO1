/*
GROUP NUMBER : 45
    LASTNAME1, FIRSTNAME1: TRINIDAD, NATHAN         SECTION1: S13
    LASTNAME2, FIRSTNAME2: DIMAUNAHAN, CHELSEA JEI  SECTION2: S14
    LASTNAME3, FIRSTNAME3: SALAMIDA, GABRIEL        SECTION3: S13
*/

#include "sort.h"

/*
    NEED TO DO:
    - find the anchor point (the point with the lowest y-coordinate, and if there are ties, 
      the one with the lowest x-coordinate)
    - sort the points based on polar angle with respect to the anchor point
    - use selection sort to sort the points based on polar angle
*/

/*
    Purpose: Locates for the anchor point in the array.
    Returns: void
    @param : points is the array of points structures where the anchor will be searched in.
    @param : n is the problem size
    Pre-condition: 
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
    Purpose: Computes the cross product of two vectors formed by three points: `a`, `b`, and `anchor`.
            The cross product determines the relative orientation of the points:
            - Positive result: Points are in counter-clockwise order.
            - Negative result: Points are in clockwise order.
            - Zero result: Points are collinear.
    Returns: A double value representing the cross product of the vectors.
    @param : a is the first point in the vector.
    @param : b is the second point in the vector.
    @param : anchor is the reference point used to calculate the vectors.
    Pre-condition: The parameters contain valid values
*/
double crossProduct(Points a, Points b, Points anchor) {
    return (a.x - anchor.x) * (b.y - anchor.y) - (a.y - anchor.y) * (b.x - anchor.x); 
        // I guess this is like final - initial formula but relative to the anchor point
}   

/*
    Purpose: Computes for the polar angles of the points relative to the anchor point.
    Returns: void
    @param : points is the array of points structures where the polar angles will be computed.
    @param : n is the problem size
    @param : anchor is the point from which the polar angles are computed.
    Pre-condition: The parameters contain valid values
*/
void computePolarAngles(Points points[], int n, Points anchor) {
    for (int i = 1; i < n; i++) {
        points[i].polarAngle = atan2(points[i].y - anchor.y, points[i].x - anchor.x);
    }
}

/*
    Purpose: Computes the squared distance between two points when two points have the same polar angle.
    Returns: the squared distance between the two points
    @param : a is the point whose distance will be computed.
    @param : anchor is the reference point from which the distance is measured.
    Pre-condition: The parameters contain valid values
*/
double distanceSquared(Points a, Points anchor) {
    double distX = a.x - anchor.x;
    double distY = a.y - anchor.y;
    return distX * distX + distY * distY;
}

/*
    Purpose: Sorts the points based on their polar angles relative to the anchor point.
             It uses selection sort to arrange the points in ascending order of polar angle.
             If two points have the same polar angle, it keeps the point that is farther from the anchor
             if the slope is negative or vertical, and keeps the point that is closer if the slope is positive.
    Returns: void
    @param : points is the array of points structures to be sorted.
    @param : n is the problem size
    Pre-condition: The parameters contain valid values
*/
void selectionSort(Points points[], int n) {
    Points anchor = points[0]; // anchor is already at index 0

    for (int i = 1; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (points[j].polarAngle < points[minIndex].polarAngle) {
                minIndex = j;
            } else if (points[j].polarAngle == points[minIndex].polarAngle) {
                // If collinear, base it on slope direction
                double dx = points[j].x - anchor.x;
                double dy = points[j].y - anchor.y;

                if (dx == 0 || dy / dx < 0) {
                    // Negative slope or vertical, keep the farther point
                    if (distanceSquared(points[j], anchor) > distanceSquared(points[minIndex], anchor)) {
                        minIndex = j;
                    }
                } else {
                    // Positive slope, keep the closer point
                    if (distanceSquared(points[j], anchor) < distanceSquared(points[minIndex], anchor)) {
                        minIndex = j;
                    }
                }
            }
        }

        if (minIndex != i) {
            Points temp = points[i];
            points[i] = points[minIndex];
            points[minIndex] = temp;
        }
    }
}

