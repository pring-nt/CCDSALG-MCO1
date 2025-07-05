/*
GROUP NUMBER : 45
    LASTNAME1, FIRSTNAME1: TRINIDAD, NATHAN         SECTION1: S13
    LASTNAME2, FIRSTNAME2: DIMAUNAHAN, CHELSEA JEI  SECTION2: S14
    LASTNAME3, FIRSTNAME3: SALAMIDA, GABRIEL        SECTION3: S13
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Purpose: Represents a 2D point with its polar angle relative to the anchor.
    Members:
        • x          — the x‑coordinate
        • y          — the y‑coordinate
        • polarAngle — the angle (in radians) from the anchor to this point
    Pre-condition:
        • All fields uninitialized until set by calling code.
*/
struct _Points {
    double x;
    double y;
    double polarAngle;
};

/*
    Purpose: Node of a singly linked stack storing Points.
    Members:
        • element — the Points value held in this node
        • pNext   — pointer to the next node in the stack (NULL if bottom)
    Pre-condition:
        • Nodes are allocated with malloc() and freed with free().
*/
typedef struct _Points Points;

struct _Stack {
    Points element;
    struct _Stack *pNext;
};

typedef struct _Stack Stack;

void createStack(Stack **);
void push(Stack **, Points);
Points pop(Stack **);
Points top(Stack *);
Points next_to_top(Stack *);
bool isEmpty(Stack *);
