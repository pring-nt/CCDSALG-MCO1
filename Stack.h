/*
GROUP NUMBER : 45
    LASTNAME1, FIRSTNAME1: TRINIDAD, NATHAN         SECTION1: S13
    LASTNAME2, FIRSTNAME2: DIMAUNAHAN, CHELSEA JEI  SECTION2: S14
    LASTNAME3, FIRSTNAME3: SALAMIDA, GABRIEL        SECTION3: S13
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct _Points {
    double x_pos;
    double y_pos;
};

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
