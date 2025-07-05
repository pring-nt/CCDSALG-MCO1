#include "graham_scan1.c"
#include <string.h>
typedef char String[25];

void promptFileNames(String src, String dest) {
    fprintf(stdout, "Enter input file name: ");
    fscanf(stdin, "%20s", src);
    fprintf(stdout, "Enter output file name: ");
    fscanf(stdin, "%20s", dest);

    String fileFormat = ".TXT";
    strcat(src, fileFormat);
    strcat(dest, fileFormat);
}

void scanInputs(FILE* fp, Points* coordinates, int size) {
    int i;
    fprintf(stdout, "Reading file...\n");
    for(i = 0; i < size; i++) {
        fscanf(fp, "%lf%lf", &coordinates[i].x, &coordinates[i].y);
    }
}

int dumpStack(Stack** stack, Points* arr) {
    int ctr = 0;
    while(!isEmpty(*stack)) {
        arr[ctr] = pop(stack);
        ctr++;
    }
    return ctr;
}

void printFile(FILE* dest, Points* convexHull, int size) {
    int i;
    fprintf(stdout, "Creating file...\n");
    fprintf(dest, "%d\n", size);
    for(i = size - 1; i >= 0; i--) {
        fprintf(dest, "%lf %lf\n", convexHull[i].x, convexHull[i].y);
    }
    fprintf(stdout, "Finished printing to file!\n");
}

int main() {
    String src;
    String dest;

    promptFileNames(src, dest);
    FILE* fpInput = fopen(src, "r");

    if (fpInput == NULL) {
        fprintf(stderr, "ERROR: File not found!\n");
        exit(1);
    }

    int size;

    fscanf(fpInput, "%d", &size);

    Points* coordinates = calloc(size, sizeof(Points));
    if(coordinates == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    Points* convexHull = calloc(size, sizeof(Points));
    if(convexHull == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    scanInputs(fpInput, coordinates, size);

    fclose(fpInput);

    Stack* hullStack = grahamScan(coordinates, size);
    int ctr = dumpStack(&hullStack, convexHull);
    FILE* fpOutput = fopen(dest, "w");

    if (fpOutput == NULL) {
        fprintf(stderr, "ERROR: Could not create file.\n");
        exit(1);
    }
    
    printFile(fpOutput, convexHull, ctr);

    fclose(fpOutput);

    free(coordinates);
    coordinates = NULL;
    free(convexHull);
    convexHull = NULL;
    if(hullStack != NULL){
        free(hullStack);
        hullStack = NULL;
    }
    return 0;
}