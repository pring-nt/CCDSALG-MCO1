/*
GROUP NUMBER : 45
    LASTNAME1, FIRSTNAME1: TRINIDAD, NATHAN         SECTION1: S13
    LASTNAME2, FIRSTNAME2: DIMAUNAHAN, CHELSEA JEI  SECTION2: S14
    LASTNAME3, FIRSTNAME3: SALAMIDA, GABRIEL        SECTION3: S13
*/

#include sort.c
#include Stack.c

void grahamscan_slow(struct Point points[], int n)
{
	// 1. Finding the minimum point (point with lowest y value) and setting it as the "anchor"
	findAnchor(points, n);
	Points anchor = points[0];

	/* 2. Remaining points are then sorted using the specified sorting algorithm based on the polar angle
	relative to the anchor */
    computePolarAngles(points, n, anchor);
	selectionSort(points, n);

	// 3. Creates and Pushes the first 2 points into the stack. Note that the anchor is guranteed to be inside the hull.
	Stack **pStack;
	createStack(&pStack);
	push(*pStack, points[0]);
	push(*pStack, points[1]);

	// 4. Iterates through every remaining element in the array
	for (int i = 2; i < n; i++)
	{
		/* the values of the previous 2 elements present inside the stack as well as the next point
		are copied into some variables */
		Points nextpoint = points[i];
		Points top = top(*pStack);
		Points nextTop = next_to_top(*pStack) ;	

		/* Removes elements that were pushed if and only if it creates a clockwise turn relative to the line created by the 
		2 previous points inside the stack .*/
		while ( /*condition that checks if the stack has at least 2 elements*/ && crossProduct(top, nextpoint, nextTop) <= 0)
			pop(*pStack);	
	
		push(*pStack, nextpoint);		
	}

	// 5. Checking if the very final point is collinear


	// 6. Freeing memory allocated to the stack
	free(pStack);
}
