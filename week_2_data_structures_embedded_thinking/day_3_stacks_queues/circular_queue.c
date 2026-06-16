#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct circular_queue
{
    int *array;
    int capacity;
    int front;
    int rear;
    int count;
} circular_queue;

circular_queue *createQueue(int capacity)
{
    circular_queue *q = (circular_queue *)malloc(sizeof(circular_queue));
    q->capacity = capacity;
    q->array = (int *)malloc(q->capacity * sizeof(int));
    q->front = 0;
    q->rear = -1;
    q->count = 0;

    return q;
}

bool isFull(circular_queue *q)
{
    return q->count == q->capacity;
}

bool isEmpty(circular_queue *q)
{
    return q->count == 0;
}

bool enqueue(circular_queue *q, int data)
{
    if (isFull(q))
        return false;
    else
    {
        q->rear = (q->rear + 1) % q->capacity;
        q->array[q->rear] = data;
        q->count++;
    }
    return true;
}

bool dequeue(circular_queue *q, int *data)
{
    if (isEmpty(q))
        return false;
    else
    {
        *data = q->array[q->front];
        q->front = (q->front + 1) % q->capacity;
        q->count--;
    }
    return true;
}

void PrintQueue(circular_queue *q)
{
    printf("Queue contents: ");
    for (int i = 0; i < q->count; i++)
    {
        int index = (q->front + i) % q->capacity;
        printf("%d ", q->array[index]);
    }
    printf("\n");
}
