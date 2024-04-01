#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

// to create a new node
struct StackNode* newNode(int data) {
    struct StackNode* node = (struct StackNode*)malloc(sizeof(struct StackNode));
    node->data = data;
    node->next = NULL;
    return node;
}

// to initialize an empty stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

// to push an element onto the stack
void push(struct Stack* stack, int data) {
    struct StackNode* node = newNode(data);
    node->next = stack->top;
    stack->top = node;
    printf("%d pushed to stack\n", data);
}

// to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    struct StackNode* temp = stack->top;
    int popped = temp->data;
    stack->top = temp->next;
    free(temp);
    return popped;
}

// to peek at the top element of the stack
int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->top->data;
}

// to print the elements of the stack
void printStack(struct Stack* stack) {
    struct StackNode* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}
