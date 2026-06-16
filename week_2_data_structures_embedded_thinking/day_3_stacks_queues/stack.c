#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
typedef struct stack
{
    int *array;
    int capacity;
    int top;
} stack;

stack *createStack(int capacity){
    stack*s=(stack*)malloc(sizeof(stack));
    s->capacity=capacity;
    s->array=(int *)malloc(s->capacity*sizeof(int));
    s->top=-1;

    return s;
}

bool isFull(stack *s){
    return s->top==s->capacity-1;
}

bool isEmpty(stack *s){
    return s->top==-1;
}

bool push(stack*s, int data){
    if(isFull(s)){
        return false;
    }
    s->array[++s->top]=data;
    return true;
}

bool pop(stack*s, int *data){
    if(isEmpty(s)){
        return false;
    }
    *data=s->array[s->top--];
    return true;
}

