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
void bubbleSort(int* arr,int len){

    for(int i=0;i<len;i++){
        for(int j=0;j<len-1-i;j++){
            if(arr[j]>arr[j+1]){
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}
void insertionSort(int* arr,int len){

    for(int i=1;i<len;i++){
        int tmp = arr[i];
        int location;
        for(int j=0;j<=i;j++){
            if(tmp<=arr[j]){
                location = j;
                break;
            }
        }
        for(int j=i;j>location;j--){
            arr[j]=arr[j-1];
        }
        arr[location]=tmp;
    }
}

void selectionSort(int* arr,int len){

    for(int i=0;i<len;i++){
        int min=__INT_MAX__;
        int minIndex;
        for(int j=i+1;j<len;j++){
            if(arr[j]<min){
                min=arr[j];
                minIndex=j;
            }
        }
        swap(&arr[i],&arr[minIndex]);
    }
}
int main(int argc, char** args){

    int arr[7] = {7,9,3,0,6,2,4};
    int* cpyArr;
    int arrLen = sizeof(arr)/sizeof(int);

    puts("array : ");
    printArr(arr,arrLen);

    puts("bubble sort : ");
    bubbleSort(cpyArr=copyArr(arr,arrLen),arrLen);
    printArr(cpyArr,arrLen);
    free(cpyArr);
    
    puts("insertion sort : ");
    insertionSort(cpyArr=copyArr(arr,arrLen),arrLen);
    printArr(cpyArr,arrLen);
    free(cpyArr);

    puts("selection sort : ");
    selectionSort(cpyArr=copyArr(arr,arrLen),arrLen);
    printArr(cpyArr,arrLen);
    free(cpyArr);

    getchar();
}