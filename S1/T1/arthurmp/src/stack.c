#include<stdio.h>
#include<stdlib.h>

#include"stack.h"

#define MAX_STACK_SIZE 50

typedef struct _stackItem {
    element elem;
}STACKITEM;

typedef struct _stack {
    int size;
    int top;
    STACKITEM *stk;
}STACK;

stack newStack() {
    STACK *stk = (STACK *) malloc(sizeof(STACK));
    if(stk == NULL) {
        printf("ERROR: Could not allocate memory for stack\n");
        exit(EXIT_FAILURE);
    }

    stk->size = 0;
    stk->top = -1;
    stk->stk = (STACKITEM *) malloc(MAX_STACK_SIZE * sizeof(STACKITEM));
    if(stk->stk == NULL) {
        printf("ERROR: Could not allocate memory for %d stack items\n", MAX_STACK_SIZE);
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < MAX_STACK_SIZE; i++) stk->stk[i].elem = NULL;

    return stk;
}

bool isStackEmpty(stack stk) {
    if(stk == NULL) return true;

    STACK *stkP = (STACK *) stk;

    return stkP->size == 0;
}

bool isStackFull(stack stk) {
    if(stk == NULL) return true;

    STACK *stkP = (STACK *) stk;

    return stkP->size == MAX_STACK_SIZE;
}

void push(stack stk, element elem) {
    if(stk == NULL || elem == NULL) return;

    if(isStackFull(stk)) {
        printf("WARNING: This stack is full\n");
        return;
    }

    STACK *stkP = (STACK *) stk;

    stkP->top++;
    if(stkP->top == MAX_STACK_SIZE) stkP->top = 0;
    stkP->stk[stkP->top].elem = elem;
    stkP->size++;
}

element pop(stack stk) {
    if(stk == NULL) return NULL;

    if(isStackEmpty(stk)) {
        printf("WARNING: This stack is empty\n");
        return NULL;
    }

    STACK *stkP = (STACK *) stk;

    element elem = stkP->stk[stkP->top].elem;
    stkP->stk[stkP->top].elem = NULL;
    stkP->top--;
    if(stkP->top < 0) stkP->top = MAX_STACK_SIZE - 1;
    stkP->size--;

    return elem;
}

element peekStack(stack stk) {
    if(stk == NULL) return NULL;

    if(isStackEmpty(stk)) {
        printf("WARNING: This stack is empty\n");
        return NULL;
    }

    STACK *stkP = (STACK *) stk;

    return stkP->stk[stkP->top].elem;
}

void destroyStack(stack stk, void (*destroyElement)()) {
    if(stk == NULL) return;

    if(destroyElement != NULL)
        while(!isStackEmpty(stk))
            destroyElement(pop(stk));

    STACK *stkP = (STACK *) stk;
    free(stkP->stk);
        
    free(stk);
    stk = NULL;
}