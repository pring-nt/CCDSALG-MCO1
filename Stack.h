#include <stdio.h>
#include <stdlib.h>

struct _stack {
        double element;
        struct _stack* pNext;
};

typedef struct _stack stack;

void createStack(stack**);
void push(stack**, double);
double pop(stack**);
double top(stack*);
double next_to_top(stack*);
int isEmpty(stack*);
