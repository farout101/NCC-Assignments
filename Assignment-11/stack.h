#ifndef STACK_H
#define STACK_H

struct StackNode {
    int data;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
};

// Functions
struct StackNode* newNode(int data);
struct Stack* createStack();
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, int data);
int pop(struct Stack* stack);
int peek(struct Stack* stack);
void printStack(struct Stack* stack);

#endif 
