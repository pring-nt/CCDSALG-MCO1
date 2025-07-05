/*
GROUP NUMBER : 45
    LASTNAME1, FIRSTNAME1: TRINIDAD, NATHAN         SECTION1: S13
    LASTNAME2, FIRSTNAME2: DIMAUNAHAN, CHELSEA JEI  SECTION2: S14
    LASTNAME3, FIRSTNAME3: SALAMIDA, GABRIEL        SECTION3: S13
*/

#include "Stack.h"

/*
    Purpose: Initializes an empty stack by setting the stack pointer to NULL.
    Returns: void
    @param  : pStack — address of the Stack* to initialize
    Pre-condition:
             - pStack must be non‑NULL.
    Post-condition:
             - *pStack is set to NULL, representing an empty stack.
*/
void createStack(Stack **pStack) {
    *pStack = NULL;
}

/*
    Purpose: Pushes a new point onto the top of the stack.
    Returns: void
    @param  : pStack — address of the Stack* to modify
    @param  : value  — Points struct to store in the new stack node
    Pre-condition:
             - pStack must be non‑NULL.
    Post-condition:
             - A new node containing 'value' is added at the top of *pStack.
             - If malloc fails, the program exits with an error.
*/
void push(Stack **pStack, Points value) {
    Stack *pNew = (Stack *)malloc(sizeof(Stack));
    if (pNew == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    pNew->element = value;
    pNew->pNext = *pStack;
    *pStack = pNew;
}

/*
    Purpose: Removes and returns the top point from the stack.
    Returns: Points — the element stored in the popped node
    @param  : pStack — address of the Stack* to modify
    Pre-condition:
             - pStack must be non‑NULL.
             - *pStack must not be empty.
    Post-condition:
             - The top node is freed.
             - *pStack is updated to its next node.
             - If the stack was empty, the program exits with an error.
*/
Points pop(Stack **pStack) {
    if (isEmpty(*pStack)) {
        fprintf(stderr, "Stack Underflow!\n");
        exit(1);
    }
    Stack *pTemp = *pStack;

    Points value = pTemp->element;
    *pStack = pTemp->pNext;
    free(pTemp);

    return value;
}

/*
    Purpose: Returns (without removing) the top point of the stack.
    Returns: Points — the element stored in the top node
    @param  : pStack — pointer to the Stack to inspect
    Pre-condition:
             - pStack must be non‑NULL.
             - pStack must not be empty.
    Post-condition:
             - The stack remains unchanged.
             - If the stack is empty, the program exits with an error.
*/
Points top(Stack *pStack) {
    if (isEmpty(pStack)) {
        fprintf(stderr, "Stack is empty!\n");
        exit(1);
    }

    Points value = pStack->element;
    return value;
}

/*
    Purpose: Returns (without removing) the second point from the top of the stack.
    Returns: Points — the element stored in the node just below the top
    @param  : pStack — pointer to the Stack to inspect
    Pre-condition:
             - pStack must be non‑NULL.
             - pStack must contain at least two nodes.
    Post-condition:
             - The stack remains unchanged.
             - If the stack has fewer than two elements, the program exits with an error.
*/
Points next_to_top(Stack *pStack) {
    if (isEmpty(pStack) || pStack->pNext == NULL) {
        fprintf(stderr, "Stack doesn't have enough elements!\n");
        exit(1);
    }

    Stack *pTemp = pStack->pNext;
    Points value = pTemp->element;
    return value;
}

/*
    Purpose: Tests whether the stack is empty.
    Returns: bool — true if the stack is empty, false otherwise
    @param  : pStack — pointer to the Stack to test
    Pre-condition:
             - pStack may be NULL or point to a valid stack.
    Post-condition:
             - The stack is unmodified.
*/
bool isEmpty(Stack *pStack) {
    return pStack == NULL;
}
