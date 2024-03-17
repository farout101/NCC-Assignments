#include "farout.h"

// Linked list functions
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL)
        (*head)->prev = newNode;
    *head = newNode;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

void displayForward(struct Node* head) {
    printf("Doubly linked list (forward): ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void displayBackward(struct Node* tail) {
    printf("Doubly linked list (backward): ");
    while (tail != NULL) {
        printf("%d ", tail->data);
        tail = tail->prev;
    }
    printf("\n");
}

void deleteNode(struct Node** head, int key) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }
    struct Node* temp = *head;
    if (temp->data == key) {
        *head = temp->next;
        if (*head != NULL)
            (*head)->prev = NULL;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != key)
        temp = temp->next;
    if (temp == NULL) {
        printf("Value not found in the list.\n");
        return;
    }
    temp->prev->next = temp->next;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    free(temp);
}

void deleteList(struct Node** head) {
    struct Node* current = *head;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Stack functions
void initStack(Stack *stack) {
    stack->top = NULL;
}

int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

void push(Stack *stack, int value) {
    struct Node* newNode = createNode(value);
    newNode->next = stack->top;
    if (stack->top != NULL)
        stack->top->prev = newNode;
    stack->top = newNode;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(1);
    }
    int data = stack->top->data;
    struct Node* temp = stack->top;
    stack->top = stack->top->next;
    if (stack->top != NULL)
        stack->top->prev = NULL;
    free(temp);
    return data;
}

int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack->top->data;
}

void deleteStack(Stack *stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
}
