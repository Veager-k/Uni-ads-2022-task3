// Lukas Brasiunas, 2110539
// https://github.com/LBrasiunas/queue_with_linked_list_in_c

#ifndef QUEUE_FUNCTION_DESC_H_INCLUDED
#define QUEUE_FUNCTION_DESC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// A linked list node to store a queue entry
typedef struct QNode
{
    double count;
    double value;
    struct QNode* next;
} QNode;

// The queue structure
typedef struct Queue
{
    struct QNode *front, *rear;
}Queue;

// A function to create a new linked list node
struct QNode* newNode(double count, double value);
// A function to create an empty queue
struct Queue* createQueue();
// A function to check if the queue is full
int isFull();
// A function to check if the queue is empty
int isEmpty(struct Queue* queue);
// A function to add a new element in to the queue and returns error = NULL if it is full
void enQueue(struct Queue* queue, double count, double value, int *error);
// A function to remove the first element from the queue
void deQueue(struct Queue* queue);
// A function to return the first element in queue
QNode* peek(struct Queue* queue);
// A function to delete an entire list
void destroyList(struct Queue* queue);
// A function to print out the entire queue
//void printList(struct Queue* queue);

#endif // QUEUE_FUNCTION_DESC_H_INCLUDED