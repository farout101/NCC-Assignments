#ifndef FAROUT_H
#define FAROUT_H

#include <stdio.h>
#include <stdlib.h>

// Structure for Linked List
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Structure for Stack
typedef struct {
    struct Node* top; // Pointer to the top node of the stack
} Stack;

// Functions for linked List
struct Node* createNode(int data);
void insertAtBeginning(struct Node** head, int data);
void insertAtEnd(struct Node** head, int data);
void displayForward(struct Node* head);
void displayBackward(struct Node* tail);
void deleteNode(struct Node** head, int key);
void deleteList(struct Node** head);

// Functions for Stack
void initStack(Stack *stack);
int isEmpty(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
int peek(Stack *stack);
void deleteStack(Stack *stack);

#endif
