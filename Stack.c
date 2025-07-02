#include "Stack.h"

void createStack(Stack** pStack) {
        *pStack = NULL;
}

void push(Stack** pStack, Points value) {
        Stack* pNew = (Stack*) malloc(sizeof(Stack));
        if (pNew == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
        }

        pNew->element = value;
        pNew->pNext = *pStack;
        *pStack = pNew;
}

Points pop(Stack** pStack) {
        if (*pStack == NULL) {
                fprintf(stderr, "Stack Underflow!\n");
                exit(1);
        }
        Stack* pTemp = *pStack;

        Points value = pTemp->element;
        *pStack = pTemp->pNext;
        free(pTemp);

        return value;
}

Points top(Stack* pStack) {
        if (pStack == NULL) {
                fprintf(stderr, "Stack is empty!\n");
                exit(1);
        }

        Points value = pStack->element;
        return value;
}

Points next_to_top(Stack* pStack) {
        if (pStack == NULL || pStack->pNext == NULL) {
                fprintf(stderr, "Stack doesn't have enough elements!\n");
                exit(1);
        }

        Stack* pTemp = pStack->pNext;
        Points value = pTemp->element;
        return value;
}

bool isEmpty(Stack* pStack) {
        return pStack == NULL;
}


