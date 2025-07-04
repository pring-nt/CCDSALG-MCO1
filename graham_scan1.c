/*
GROUP NUMBER : 45
    LASTNAME1, FIRSTNAME1: TRINIDAD, NATHAN         SECTION1: S13
    LASTNAME2, FIRSTNAME2: DIMAUNAHAN, CHELSEA JEI  SECTION2: S14
    LASTNAME3, FIRSTNAME3: SALAMIDA, GABRIEL        SECTION3: S13
*/

#include "sort.h"

/*
    Purpose: Computes the cross product of two vectors formed by three points: `a`, `b`, and `anchor`.
            The cross product determines the relative orientation of the points:
            - Positive result: Points are in counter-clockwise order.
            - Negative result: Points are in clockwise order.
            - Zero result: Points are collinear.
    Returns: A double value representing the cross product of the vectors.
    @param : top is the top point in the stack.
    @param : new is the new point being checked.
    @param : nextToTop is the reference point used to calculate the vectors.
    Pre-condition: The parameters contain valid values
*/
double crossProduct(Points top, Points new, Points nextToTop) {
    return (top.x - nextToTop.x) * (new.y - nextToTop.y) - (top.y - nextToTop.y) * (new.x - nextToTop.x); 
        // Finds the cross product of 2 points relative to an anchor
}   

Stack* grahamScan(Points points[], int n) {
    int i;
    Points nextPoint;
	Points topPoint;
	Points nextToTop;	

	// 1. Finding the minimum point (point with lowest y value) and setting it as the "anchor"
	findAnchor(points, n);
	Points anchor = points[0];

    // Edge Cases:
    // 0 points -> empty hull
    if (n == 0) {
        Stack *empty;
        createStack(&empty);
        return empty;
    }

    // 1 point -> hull is that one point
    if (n == 1) {
        Stack *h;
        createStack(&h);
        push(&h, points[0]);
        return h;
    }

    // 2 points -> hull is both points (even if collinear)
    if (n == 2) {
        Stack *h;
        createStack(&h);
        push(&h, points[0]);
        push(&h, points[1]);
        return h;
    }

	/* 2. Remaining points are then sorted using the specified sorting algorithm based on the polar angle
	relative to the anchor */
    computePolarAngles(points, n);
	selectionSort(points, n);

    // All points are collinear edge case
    bool allCollinear = true;
    bool exitFlag = false;

    for (i = 2; i < n && ! exitFlag; i++) {
        if (crossProduct(points[i-2], points[i-1], points[i]) != 0) {
            allCollinear = false;
            exitFlag = true;
        }
    }

    if (allCollinear) {
        // Strict hull: just endpoints
        Stack *h;
        createStack(&h);
        push(&h, points[0]);       // the anchor point
        
        int max = 1;
        for (i = 2; i < n; i++) {  // Search for the point with the largest distance from the anchor
            if(distanceSquared(points[0], points[max]) < distanceSquared(points[0], points[i])) {
                max = i;
            }
        }
        
        push(&h, points[max]);

        return h;
    }

	// 3. Creates and Pushes the first 2 points into the stack. Note that the anchor is guranteed to be inside the hull.
	Stack *pStack;
	createStack(&pStack);
	push(&pStack, points[0]);
	push(&pStack, points[1]);

	// 4. Iterates through every remaining element in the array
	for (i = 2; i < n; i++) {
		/* the values of the previous 2 elements present inside the stack as well as the next point
		are copied into some variables */
		nextPoint = points[i];
		topPoint = pop(&pStack);	

		/* Removes elements that were pushed if and only if it creates a clockwise turn relative to the line created by the 
		2 previous points inside the stack .*/
		while ( !isEmpty(pStack) && crossProduct(topPoint, nextPoint, top(pStack)) <= 0) {
            printf("Deleting %lf %lf\n", topPoint.x, topPoint.y);
			topPoint = pop(&pStack); // Delete the points that are causing a clockwise turn
        }
		push(&pStack, topPoint); // push the last point that DIDN'T cause a clockwise turn
        push(&pStack, nextPoint); // push the next point
	}

	// 5. Checking if the very final point is collinear
    nextToTop = next_to_top(pStack);
    topPoint = top(pStack);
    if (crossProduct(topPoint, anchor, nextToTop) <= 0) { // Check if it is collinear
        pop(&pStack); // Delete that element since it is collinear
    }
    return pStack;
}
