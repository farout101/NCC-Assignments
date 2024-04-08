#ifndef QUEUE_H
#define QUEUE_H

struct QueueNode {
    int data;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *front, *rear;
};

struct QueueNode *newNode(int data);
struct Queue *createQueue();
int isEmptyQueue(struct Queue *queue);
void enqueue(struct Queue *queue, int data);
int dequeue(struct Queue *queue);
void emptyQueue(struct Queue *queue);
void displayQueue(struct Queue *queue);

#endif
