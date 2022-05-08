//https://github.com/Danielius4/ADS/blob/main/ADS1
#ifndef STACK_H_
#define STACK_H_

typedef struct Node
{
    double count;
    double value;
    struct Node *link;
}Node;

typedef struct Stack
{
    Node *head;
}Stack;

int init(Stack *a); // initializes Stack structure elements

int createStack(Stack *a);
int deleteStack(Stack *a);
int push(Stack *a, double count, double value);
Node* pop(Stack *a);
int isStackFull(Stack a);
int isStackEmpty(Stack a);
Node* peekStack(Stack a);

int countStackElements(Stack a);
Node* findData(Stack a, int location);  // finds data at location from the top
int deleteNodeByLocation(Stack *a,int location); // deletes stack element at location from the top


#endif