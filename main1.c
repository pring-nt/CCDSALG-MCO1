/*
GROUP NUMBER : 45
    LASTNAME1, FIRSTNAME1: TRINIDAD, NATHAN         SECTION1: S13
    LASTNAME2, FIRSTNAME2: DIMAUNAHAN, CHELSEA JEI  SECTION2: S14
    LASTNAME3, FIRSTNAME3: SALAMIDA, GABRIEL        SECTION3: S13
*/

#include "graham_scan1.c"
#include <string.h>
typedef char String[25];

void promptFileNames(String, String);
void scanInputs(FILE*, Points*, int);
int dumpStack(Stack**, Points*);
void printFile(FILE*, Points*, int);

int main() {
    String src;
    String dest;

    // Prompt the user for input and output file names (without extension)
    promptFileNames(src, dest);

    // Open the input file for reading
    FILE* fpInput = fopen(src, "r");
    if (fpInput == NULL) {
        fprintf(stderr, "ERROR: File not found!\n");
        exit(1);
    }

    // Read the number of points from the first line
    int size;
    fscanf(fpInput, "%d", &size);

    // Allocate array to hold the input coordinates
    Points* coordinates = calloc(size, sizeof(Points));
    if (coordinates == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    // Allocate array to hold the convex hull result (max size = size)
    Points* convexHull = calloc(size, sizeof(Points));
    if (convexHull == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    // Read the point coordinates from the file into the array
    scanInputs(fpInput, coordinates, size);

    // Close the input file now that we've read all data
    fclose(fpInput);

    // Compute the convex hull, returned as a stack of hull vertices
    Stack* hullStack = grahamScan(coordinates, size);

    // Pop the stack into our convexHull array, ctr = number of hull points
    int ctr = dumpStack(&hullStack, convexHull);

    // Open the output file for writing the hull
    FILE* fpOutput = fopen(dest, "w");
    if (fpOutput == NULL) {
        fprintf(stderr, "ERROR: Could not create file.\n");
        exit(1);
    }

    // Write the hull size and the points themselves to the output file
    printFile(fpOutput, convexHull, ctr);

    // Close the output file when done
    fclose(fpOutput);

    // Clean up dynamically allocated memory
    free(coordinates);
    coordinates = NULL;

    free(convexHull);
    convexHull = NULL;

    // If any stack structure remains, free it (should be empty after dumpStack)
    if (hullStack != NULL) {
        free(hullStack);
        hullStack = NULL;
    }

    return 0;
}

/*
    Purpose: Prompts the user for an input and output file name (without extension),
             reads each into the provided buffers, and appends the “.TXT” extension.
    Returns: void
    @param  : src  — buffer (at least 24 chars) where the input file name will be stored
    @param  : dest — buffer (at least 24 chars) where the output file name will be stored
    Pre-condition:
             - src and dest must point to writable char arrays of sufficient size.
             - stdin and stdout must be available.
    Post-condition:
             - src and dest each contain the entered name plus “.TXT” appended.
*/
void promptFileNames(String src, String dest) {
    fprintf(stdout, "Enter input file name: ");
    fscanf(stdin, "%20s", src);
    fprintf(stdout, "Enter output file name: ");
    fscanf(stdin, "%20s", dest);

    String fileFormat = ".TXT";
    strcat(src, fileFormat);
    strcat(dest, fileFormat);
}

/*
    Purpose: Reads 'size' pairs of floating‑point coordinates from the open file
             pointed to by fp into the coordinates array.
    Returns: void
    @param  : fp           — pointer to an open FILE (must be opened for reading)
    @param  : coordinates  — array of Points structs to fill (length >= size)
    @param  : size         — number of point pairs to read 
    Pre-condition:
             - fp is non‑NULL and opened for reading.
             - coordinates points to an array with at least 'size' elements.
    Post-condition:
             - coordinates[0..size-1] are populated with x,y values read from fp.
*/
void scanInputs(FILE* fp, Points* coordinates, int size) {
    int i;
    fprintf(stdout, "Reading file...\n");
    for(i = 0; i < size; i++) { // Scan each row of the file.
        fscanf(fp, "%lf%lf", &coordinates[i].x, &coordinates[i].y);
    }
}

/*
    Purpose: Pops all Points from the stack into the provided array in pop order
             and returns the count of items popped.
    Returns: int — the number of Points popped into 'arr'
    @param  : stack — pointer to the Stack* to be emptied (will be modified)
    @param  : arr   — array of Points to receive the popped values (length >= number of elements in stack)
    Pre-condition:
             - stack points to a valid, possibly non‑empty stack.
             - arr points to writable memory with sufficient capacity.
    Post-condition:
             - arr[0..return-1] contains the popped Points, in LIFO order.
             - *stack is empty and freed when this function returns.
*/
int dumpStack(Stack** stack, Points* arr) {
    int ctr = 0;
    // Empty out the stack while repeatedly popping it and storing the popped value
    while(!isEmpty(*stack)) {
        arr[ctr] = pop(stack);
        ctr++;
    }
    // return the amount of popped elements stored into arr.
    return ctr; 
}
/*
    Purpose: Writes the convex hull to the output file 'dest' in reverse order
             (so the first printed point is the anchor), preceded by the count,
             and logs status messages to stdout.
    Returns: void
    @param  : dest       — pointer to an open FILE (must be opened for writing)
    @param  : convexHull — array of Points representing the hull (length ≥ size)
    @param  : size       — number of Points in 'convexHull'
    Pre-condition:
             - dest is non‑NULL and opened for writing.
             - convexHull points to an array with at least 'size' elements.
    Post-condition:
             - dest file contains 'size' on the first line, then each hull point
               in "x y" format on its own line, in reverse array order.
             - Status messages "Creating file…" and "Finished printing to file!"
               have been written to stdout.
*/
void printFile(FILE* dest, Points* convexHull, int size) {
    int i;
    fprintf(stdout, "Creating file...\n");
    fprintf(dest, "%d\n", size); // Print the amount of hull points pairs first
    for(i = size - 1; i >= 0; i--) { // Print the points itself in reverse order
        fprintf(dest, "%lf %lf\n", convexHull[i].x, convexHull[i].y);
    }
    fprintf(stdout, "Finished printing to file!\n");
}