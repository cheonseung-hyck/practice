#include "heap.h"
#include<stdio.h>
#include<stdlib.h>

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int* copyArr(int* arr,int len){
    int* res = (int*)malloc(len*sizeof(int));

    for(int i=0;i<len;i++){
        res[i] = arr[i];
    }

    return res;
}
void printArr(int* arr,int len){

    for(int i=0;i<len;i++){
        printf("%d ",arr[i]);
    }
    putchar('\n');
}

void merge(int* arr,int start,int end){

    int length = end-start+1;
    int* resArr = (int*)malloc(sizeof(int)*length);
    int mid = (start+end)/2;
    for(int i=start,j=mid+1,k=0;;){
        if(arr[i]>arr[j]){
            resArr[k]=arr[j];
            j++;
            k++;
            if(j>end){
                while(i<=mid){
                    resArr[k]=arr[i];
                    k++;
                    i++;
                }
                break;
            }            
        }
        else{
            resArr[k]=arr[i];
            i++;
            k++;
            if(i>mid){
                while(j<=end){
                    resArr[k]=arr[j];
                    k++;
                    j++;
                }
                break;
            } 
        }
    }
    for(int i=start,j=0;i<=end;i++,j++){
        arr[i] = resArr[j];
    }
    free(resArr);
    
}
void mergeSort(int* arr,int start,int end){
    
    if(end-start<1)
        return;
    
    int middle = (start+end)/2;
    mergeSort(arr,start,middle);
    mergeSort(arr,middle+1,end);
    merge(arr,start,end);
    
    
}
void heapSort(int* arr,int len){

    heap* h = (heap*)malloc(sizeof(heap));

    for(int i=0;i<len;i++){
        push(h,arr[i]);
    }
    for(int i=0;i<len;i++){
        arr[i]=pop(h);
    }
    free(h);
}

int main(int argc, char** args){

    int arr[7] = {7,9,3,0,6,2,4};
    int* cpyArr;
    int arrLen = sizeof(arr)/sizeof(int);

    puts("array : ");
    printArr(arr,arrLen);

    puts("bubble sort : ");
    mergeSort(cpyArr=copyArr(arr,arrLen),0,arrLen-1);
    printArr(cpyArr,arrLen);
    free(cpyArr);

    puts("heap sort : ");
    heapSort(cpyArr=copyArr(arr,arrLen),arrLen);
    printArr(cpyArr,arrLen);
    free(cpyArr);

    getchar();
}
