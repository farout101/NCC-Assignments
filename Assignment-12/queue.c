#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// to create a first ever queue node
struct QueueNode* newNode(int data) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// to check if the queue is empty
int isEmptyQueue(struct Queue* queue) {
    return (queue->front == NULL);
}

// to add a new element to the queue
void enqueue(struct Queue* queue, int data) { 
    struct QueueNode* temp = newNode(data);
    if (isEmptyQueue(queue)) {
        queue->front = queue->rear = temp;
        return;
    }
    queue->rear->next = temp; 
    queue->rear = temp;  
}

// just a typical dequeue
int dequeue(struct Queue* queue) {
    if (isEmptyQueue(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    struct QueueNode* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    free(temp);
    return data;
}

// to clear the queue
void emptyQueue(struct Queue* queue) {
    while (!isEmptyQueue(queue)) {
        dequeue(queue);
    }
}

// to display the entire queue
void displayQueue(struct Queue* queue) {
    struct QueueNode* current = queue->front;
    if (isEmptyQueue(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
