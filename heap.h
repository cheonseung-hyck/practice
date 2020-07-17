
#ifndef HEAP
#define HEAP
#include <cstddef>

struct heap{

    heap* next=NULL;
    int value;
    int index=1;
};

void push(heap* arr,int v);
int pop(heap* arr);
heap* getLeft(heap* arr);
heap* getRight(heap* arr);
heap* getParent(heap* root,heap* arr);
void swap(int* a,int* b);
int min(int a,int b);

#endif