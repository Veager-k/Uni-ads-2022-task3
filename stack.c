#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

int createStack(Stack *a)       // returns 1 if everything is ok
{                               // returns 0 if memory can't be allocated
    if(a->head != NULL)         // returns -9999 if stack head is not NULL
    {
        return -9999;
    }

    if((a->head = (struct Node*)malloc(sizeof(struct Node))) == NULL)
        return 0;

    (a->head)->link = NULL;

    return 1;
}

int countStackElements(Stack a)     // returns number of elements in the stack
{                                   
    int counter;

    if(a.head == NULL)
        return 0;

    else
    {
        struct Node *current = NULL;

        counter = 1;
        current = a.head;

        while(current->link != NULL)
        {
            counter++;
            current = current->link;
        }
    }
    return counter;
}

int deleteStack(Stack *a)           // delete stack from memory, free memory
{                                   // returns -9999 if list does not exist
    if(a->head == NULL)             // returns 1 if success
    {
        return -9999;
    }
    Node *current = a->head;
    while(current != NULL)
    {
        current = a->head->link;
        free(a->head);
        a->head = current;
    }

    return 1;
}

int push(Stack *a, double count, double value)        // push new element
{                                   // returns -9999 if stack is full
    if(isStackFull(*a) == 1){
        return -9999;
    }

    Node *current = (struct Node*)malloc(sizeof(struct Node));

    current->link = a->head;
    current->count = count;
    current->value = value;
    a->head = current;
    return 1;
}

int deleteNodeByLocation(Stack *a ,int location)    // delete data at specified location
{                                                   // returns -9999 if error
    if(location < 1)                                // returns 1 if success
    {
        return -9999;
    }
    if(a == NULL)
    {
        return -9999;
    }
    Node *prev = NULL;
    Node *current = NULL;

    current = a->head;
    prev = a->head;
    for(int i = 1; i < location; ++i)
    {
        if(current->link == NULL)
        {
            return -9999;
        }
        prev = current;
        current = current->link;
    }
    if(current == a->head)
    {
        a->head = a->head->link;
        free(current);
        return 1;
    }
    if(current->link == NULL)
    {
        prev->link = NULL;
        free(current);
    }
    else
    {
        prev->link = current->link;
        free(current);
    }
    return 1;
}

Node* findData(Stack a, int location)         // find data at specified location
{                                           // returns 0 if stack is empty or does not exist
    int nodes = countStackElements(a);
    if(nodes > 0)
    {
        if(a.head == NULL)
        { 
            return 0;
        }
        Node *current = a.head;
        for(int i = 1; i != location; ++i)
        {
            if(current->link == NULL)
            {
                return 0;
            }
            current = current->link;
        }
        return current;
    }
    return 0;
}

Node* peekStack(Stack a)
{
    return a.head;
}

Node* pop(Stack *a)               //returns 0 if stack is empty
{                               //returns first element of stack
    if(countStackElements(*a) > 0)
    {
        Node* data = findData(*a, 1);

        deleteNodeByLocation(a, 1);
        return data;
    }
    else
        return 0;
}

int isStackFull(Stack a)            //returns 1 if stack is full
{                                   //returns 0 if stack is not full
    if(a.head == NULL)              //returns -9999 if stack is not created
    {
        return -9999;
    }
    if((a.head = (struct Node*)malloc(sizeof(struct Node))) == NULL)
    {
        return 1;
    }
    else
    {
        free(a.head);
        return 0;
    }
}

int isStackEmpty(Stack a)               //returns 1 if stack is empty
{                                       //returns 0 if stack is not empty
    if(a.head == NULL)                  //returns -9999 if stack is not created
        return -9999;

    if(countStackElements(a) == 0)
        return 1;
    else
        return 0;
}

int init(Stack *a)
{
    a->head = NULL;

    return 1;
}