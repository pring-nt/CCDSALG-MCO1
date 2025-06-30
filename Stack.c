#include "Stack.h"

void createStack(stack** pStack) {
        *pStack = NULL;
}

void push(stack** pStack, double value) {
        stack* pNew = (stack*) malloc(sizeof(stack));
        if (pNew == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
        }

        pNew->element = value;
        pNew->pNext = *pStack;
        *pStack = pNew;
}

double pop(stack** pStack) {
        if (*pStack == NULL) {
                fprintf(stderr, "ERROR: Stack Underflow!\n");
                exit(1);
        }
        stack* pTemp = *pStack;
        double value = pTemp->element;
        *pStack = pTemp->pNext;
        free(pTemp);

        return value;
}

double top(stack* pStack) {
        if (pStack == NULL) {
                fprintf(stderr, "ERROR: Stack is empty!\n");
                exit(1);
        }

        return pStack->element;
}

double next_to_top(stack* pStack) {
if (pStack == NULL || pStack->pNext == NULL) {
        fprintf(stderr, "ERROR: Stack doesn't have enough elements!\n");
                exit(1);
        }

        return pStack->pNext->element;
}

int isEmpty(stack* pStack) {
        return pStack == NULL;
}
