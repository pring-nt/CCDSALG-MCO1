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
    Purpose: Computes for the polar angles of the points relative to the anchor point.
    Returns: void
    @param : points is the array of points structures where the polar angles will be computed.
    @param : n is the problem size
    @param : anchor is the point from which the polar angles are computed.
    Pre-condition: The parameters contain valid values
*/
void computePolarAngles(Points points[], int n) {
    Points anchor = points[0];
    points[0].polarAngle = 0; // The first element of points should already be the anchor
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

/*
	Purpose: Sorts the points based on their polar angles relative to the anchor point.
         	This is the first part of a merge sort algorithm that recursively divides the points array to different
         	subarrays that are then sorted and merged together by another helper function referred to as merge.

	Returns: void
	@param : points is the array of points structures to be sorted.
	@param : left is the index of the first point to be sorted inside the points array (in this case, index 1)
	@param : right is the index of the last point to be sorted inside the points array (in this case, index size-1)
	Pre-condition: Assumes functions findAnchor() and computePolarAngles() are already called prior and that the values
               	passed are valid.  
*/ 

// left must be called with 1 within the driver, right is size - 1
void mergeSort(Points points[], int left, int right)
{
	if (left < right)
	{
    	int mid = left + (right - left) / 2;

    	/* divides and sorts the first half recursively before
    	doing the same to the second half */
    	mergeSort(points, left, mid);
    	mergeSort(points, mid + 1, right);

    	// merges sorted subarrays
    	merge(points, left, mid, right);    
	}   	 
}

/*
	Purpose: Sorts the points based on their polar angles relative to the anchor point.
         	This is the second part of a merge sort algorithm that merges the sub arrays that were previously divided.
         	This function sorts in ascending order by comparing the polar angles of the two points from the left and right sub arrays
         	and copies them back into the points array.

         	In the case that two points contain the same polar angle. This function keeps the point that is farther from the anchor,
         	if the slope is negative or vertical, and keeps the point that is closer if the slope is positive.

	Returns: void
	@param : points is the array of points structures to be sorted.
	@param : l is the leftmost index or simply the first point to be sorted inside the points array (in this case, index 1)
	@param : m is the middle value of the range of elements to be sorted
	@param : r is the rightmost index or simply the last point to be sorted inside the points array (in this case, index size-1)
	Pre-condition: Assumes functions findAnchor() and computePolarAngles() are already called prior and that the values
               	passed are valid.  
*/

void merge(Points points[], int l, int m, int r)
{
	int left_length = m - l + 1;
	int right_length = r - m;    

	// temporary arrays
	Points temp_left[left_length];
	Points temp_right[right_length];
	Points anchor = points[0];

	/* indices for merging step : i for temp_left,
	j for temp_right, k for the points array */
	int i = 0, j = 0, k;
	k = l;		

	// copying contents of left side of array to temp_left
	for (int i = 0; i < left_length; i++)
    	temp_left[i] = points[l + i];    

	/* copying contents of right side of array to temp_right.
	indexed starting from mid value + 1 to copy the right side */
	for (int i  = 0; i < right_length; i++)
    	temp_right[i] = points[(m + 1) + i];    


	// merging sorted sub arrays
	while (i  < left_length && j < right_length)
	{
		if (temp_left[i].polarAngle < temp_right[j].polarAngle)	
		{		
        	points[k] = temp_left[i];
        	i++;   	 
			k++;
    	}   	 
    	else if (temp_left[i].polarAngle > temp_right[j].polarAngle)	
		{
	       	points[k] = temp_right[j];
        	j++;
			k++;	
		}		
		else // collinear
		{
			/* since its collinear , both points contain the same slope 
		    its therefore possible to just test 1 point to identify if it contains a
			neg/pos slope or within the vertical */	   
			double dx = temp_left[i].x - anchor.x;
			double dy = temp_left[i].y	- anchor.y;

			if (dx == 0 || dy / dx < 0)
			{
				// keep the farther point 
				if (distanceSquared(temp_left[i], anchor) > distanceSquared(temp_right[j], anchor)) 
				{
					points[k] = temp_left[i];
					i++;   	 
					k++;			
				}
				else 
				{
				   	points[k] = temp_right[j];
					j++;
					k++;			
				}					
			}
			else
			{
				// keep the closer point	
				if (distanceSquared(temp_left[i], anchor) > distanceSquared(temp_right[j], anchor)) 
				{
				   	points[k] = temp_right[j];
					j++;
					k++;		
				}
				else 
				{
					points[k] = temp_left[i];
					i++;   	 
					k++;
				}		
			}		
    	}				
	}

	// copies leftover elements if there exists leftovers within the subarrays 
	while (i  < left_length)
	{
      	points[k] = temp_left[i];
		i++;   	 
		k++;	
	}

	while (j < right_length)
	{
      	points[k] = temp_right[j];
     	j++;
		k++;	
	}
}
