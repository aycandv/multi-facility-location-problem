
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT 1
#define type int

/** @description: Min binary heap
* 
* */

typedef struct binary_heap{
   
    size_t size;
    size_t capacity;
    int * ptr;
}binary_heap;


void init_binary(binary_heap * heap){
   heap->ptr = malloc(sizeof(type)*DEFAULT);
    heap->capacity=DEFAULT;
    heap->size = 0;
}

size_t size(binary_heap * heap){
    return heap->size;
}

int isEmpty(binary_heap * heap){
    return (heap->size == 0);
}


int parentNode(int i ){
    return (i-1)/2;
}

int leftChild(int i){
    return (2*i)+1;
}

int rightChild(int i){
    return (2*i)+2;
}


int hasLeftChild(int i ,binary_heap * heap){
    return leftChild(i)<heap->size;
}

int hasRightChild(int i, binary_heap *heap){
    return rightChild(i)<heap->size;
}

void upheap(int i ,binary_heap * heap){
    while (i>0)
    {
       int p = parentNode(i);
       if(heap->ptr[p] == heap->ptr[i] || heap->ptr[i]>heap->ptr[p]){
           break;
       }
       int temp = heap->ptr[p];
       heap->ptr[p] = heap->ptr[i];
       heap->ptr[i] = temp;
        i = p;
    }
    
}

void downheap(int i, binary_heap * heap){
    int ii = heap->size;
    if(heap->size == 2){
        int x = 5;
    }
    while (hasRightChild(i,heap)|| hasLeftChild(i,heap))
    {
        int smallChild = leftChild(i);
        
        if(hasRightChild(i,heap)){
            int rc = rightChild(i);
            if(heap->ptr[rc] < heap->ptr[smallChild]){
                smallChild = rc;
            }
        }

     if(heap->ptr[smallChild] == heap->ptr[i] || heap->ptr[smallChild]>heap->ptr[i]){
           break;
       }
       int temp = heap->ptr[smallChild];
       heap->ptr[smallChild] = heap->ptr[i];
       heap->ptr[i] = temp;
        i = smallChild;

    }
    
}

int pop(binary_heap * heap){
    if(isEmpty(heap)){
        return 0;
    }

    int old = heap->ptr[0];
    // int temp = heap->ptr[heap->size-1];
     heap->ptr[0] = heap->ptr[heap->size-1];
     heap->ptr[heap->size-1] = 0;
     heap->size --;
     downheap(0,heap);
     return old;
}



int top(binary_heap * heap){
    if(isEmpty(heap)){
        return 0;
    }
    return heap->ptr[0];
}

void resize(binary_heap * heap){
    heap->ptr = realloc(heap->ptr, heap->capacity*2*sizeof(type));
}

void insert(int i , binary_heap* heap){

    if(heap->size >= heap->capacity){
        resize(heap);
    }
    (heap->ptr)[heap->size] = i;
    heap->size = heap->size +1;
    upheap(heap->size-1,heap);
}

void print_heap(binary_heap * heap){
    printf("Heap : ");
    for(int i = 0; i< heap->size; i++){
        printf(" %d ",heap->ptr[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int arrA [] = {3,2,1,7,8,4,10,16,12};
    binary_heap  heap;
    init(&heap);
    
        printf("Original Array : ");

        for(int i=0;i<9;i++){
            printf("   %d ",arrA[i]);
            insert(arrA[i],&heap);
        }
        printf("\n");
        print_heap(&heap);
       printf("Calling pop ! \n");

    for(int i=0;i<9;i++){
            printf("   %d ",pop(&heap));}
            

    return 0;
}



