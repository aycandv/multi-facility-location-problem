#include <stdio.h>
#include <stdlib.h>


#define size_int sizeof(int)
#define size_intptr sizeof(int *) 

#define INF2 (INT32_MAX)   //99999995 

void init_vertexr(int ***ptr,int size);

int readFile(int* graph_size,int ** weight, int *** vertex, const char * filename){
    FILE * fp;
    fp = fopen(filename,"r");

    if(fp == NULL){
        printf("File could not open! \n");
        return -1;
    }

    int size = 0;
    int temp1 = 0;
    int temp = 0;
    int temp3 = 0;
    int temp2 = 0;
    fscanf(fp,"%d",&size);

    printf("%d\n",size);

    if(size == 0){
        printf("Error in reading the file !\n");
        return -1;
    }
    *graph_size = size;

    (*weight) = malloc(size_int*size);
    fscanf(fp,"%d",&temp);
    for (size_t i = 0; i < size; i++)
    {
        fscanf(fp,"%d %d",&temp1, &temp2);
        (*weight)[temp1] = temp2;
    }

    (*vertex) = malloc(size_intptr*size);

    for (size_t i = 0; i < size; i++)
    {
        (*vertex)[i] = malloc(size_int*size);
    }

    fscanf (fp, "%d %d %d", &temp1,&temp2,&temp3);    

    (*vertex)[temp1][temp2] = temp3;

    while (!feof (fp))
    {  
       fscanf (fp, "%d %d %d", &temp1,&temp2,&temp3);  
       ((*vertex)[temp1])[temp2] = temp3;   
        ((*vertex)[temp2])[temp1] = temp3;
    }

    fclose(fp);
    init_vertexr(vertex,size);
    return 1;
}


void print_array(size_t size, int *ptr){
    for (size_t i = 0; i < size; i++)
    {
        printf("ID : %d weight : %d",i,ptr[i]);
        printf("\n");
    }    
}

void init_vertexr(int ***ptr,int size){
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if((*ptr)[i][j] == 0){
                if(i != j){
                    (*ptr)[i][j] = INF2;
                }
            }
        }
        
    }
    
}
void print2d_array(size_t size, int **ptr){
      for (size_t i = 0; i < size; i++){
        
        for (size_t j = 0; j < size; j++){
            if(ptr[i][j] == INF2){
                printf("INF ");
            } else {
                printf ("%d  ", ptr[i][j]);
            }
            
        }
        printf("\n");
        }
}