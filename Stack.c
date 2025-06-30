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

bool pop(Stack** pStack, Points* outPoint) {
        if (*pStack == NULL) {
                fprintf(stderr, "Stack Underflow!\n");
                return false;
        }
        Stack* pTemp = *pStack;

        *outPoint = pTemp->element;
        *pStack = pTemp->pNext;
        free(pTemp);

        return true;
}

bool top(Stack* pStack, Points* outPoint) {
        if (pStack == NULL) {
                fprintf(stderr, "Stack is empty!\n");
                return false;
        }
        *outPoint = pStack->element;
        return true;
}

bool next_to_top(Stack* pStack, Points* outPoint) {
        if (pStack == NULL || pStack->pNext == NULL) {
                fprintf(stderr, "Stack doesn't have enough elements!\n");
                return false;
        }

        Stack* pTemp = pStack->pNext;
        *outPoint = pTemp->element;
        return true;
}

bool isEmpty(Stack* pStack) {
        return pStack == NULL;
}
