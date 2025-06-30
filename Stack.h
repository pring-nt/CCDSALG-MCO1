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
        struct _Stack* pNext;
};

typedef struct _Stack Stack;

void createStack(Stack**);
void push(Stack**, Points);
bool pop(Stack**, Points*);
bool top(Stack*, Points*);
bool next_to_top(Stack*, Points*);
bool isEmpty(Stack*);
