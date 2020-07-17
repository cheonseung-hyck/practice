#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

heap* getLeft(heap* arr){
    heap* next=arr;
    for(int i=arr->index;i<(arr->index)*2;i++){
        next=next->next;
    }
    return next;
}
heap* getRight(heap* arr){
    heap* next=arr;
    for(int i=arr->index;i<(arr->index)*2+1;i++){
        next=next->next;
    }
    return next;
}
void swap(int* a,int* b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
int min(int a,int b){
    return a>b?b:a;
}
heap* getParent(heap* root,heap* arr){
    heap* next=root;
    for(int i=0;i<(arr->index)/2;i++){
        next=next->next;
    }
    return next;
}
void push(heap* arr,int v){
    printf("%d\n",v);
    if((arr->next)==NULL){
        arr->value==v;
        return;
    }
    heap* next=arr;
    heap* newNode = (heap*)malloc(sizeof(heap));
    int index=2;
    while(true){
       
        if(next->next==NULL){
            next->next=newNode;
            newNode->index=index;
            break;
        }
        else{
            next=next->next;
            index++;
        }  
    }
    next=newNode;
    while(true){
        if(next->value<v){
            break;
        }
        else{
            heap* tmp=next;
            next=getParent(arr,next);
            swap(&(tmp->value),&(next->value));
        }
    }
}
int pop(heap* arr){

    int result=arr->value;
    if(arr->next==nullptr){
        return result;
    }

    int maxChild;
    heap* next=arr;
    while(true){
        if(!(next->value<=min(getLeft(next)->value,getRight(next)->value))){
            if(getLeft(next)->value<getRight(next)->value){
                heap* tmp=next;
                next=getLeft(next);
                swap(&(tmp->value),&(next->value));
            }
            else{
                heap* tmp=next;
                next=getRight(next);
                swap(&(tmp->value),&(next->value));
            }
        }
        else{
            break;
        }
    }
    return result;
}

int main(int a, char** b){
    heap* h = (heap*)malloc(sizeof(heap));

    push(h,5);push(h,9);push(h,0);push(h,8);push(h,33);push(h,28);

    for(int i=0;i<6;i++){
        printf("%d ",pop(h));
    }
}