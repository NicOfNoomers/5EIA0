#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 30

struct person_t{
    char *name;
    float height;
};

struct person_t persons[MAXLEN];

void freeHeap(struct person_t database[]){
    for(int i=0;i<MAXLEN;i++){
        free(database[i].name);
    }
}

void printValues(struct person_t database[], int from, int to){
    printf("[");
    for(int i=from;i<to;i++){
        printf("(\"%s,%.3f\"),",database[i].name,database[i].height);
    }
    printf("]\n");
}

void initialise(struct person_t database[], int size){
    if (size>0 && size<=MAXLEN) {
        for (int i=0;i<size;i++){
            database[i].name = (char *) malloc (10*sizeof(char));
            sprintf(database[i].name,"person %d",i);
            database[i].height = size-1-i;
        }
    }  
    else{
        printf("Array size must be from 1 to 30.\n");
    }
}

float largestElement(struct person_t database[], int size){
    float max = database[0].height;
    for(int i =1;i<size;i++){
        if  (max<database[i].height){
            max = database[i].height;
        }
    }
    return max;
}

float smallestElement(struct person_t database[], int size){
    float min = database[0].height;
    for(int i =1;i<size;i++){
        if  (min>database[i].height){
            min = database[i].height;
        }
    }
    return min;
}

void replaceElement(struct person_t database[],int index,int size){
    if  (index>=size){
        printf("Index is out of range!\n");
    }
    else{
        char newstring[100];
        float height;
        printf ("Name? ");
        scanf (" %[^\n]s", &newstring);
        free(database[index].name);
        database[index].name = (char *) malloc (strlen(newstring)+1);
        strcpy (database[index].name,newstring);
        printf ("Height? ");
        scanf (" %f", &database[index].height);
    }
}

void insertionsort(struct person_t database[], int size){
    struct person_t temp;
    for(int i=0;i<size;i++){
        for (int j=i+1;j<size;j++){
            if (database[i].height>=database[j].height){
                if  (database[i].height==database[j].height && strcmp(database[i].name,database[j].name)>0){
                    temp = database[i];
                    database[i] = database[j];
                    database[j] = temp;
                    printf("after swapping: ");
                    printValues(database,0,size);  
                }
                else{
                    temp = database[i];
                    database[i] = database[j];
                    database[j] = temp;
                    printf("after swapping: ");
                    printValues(database,0,size);
                }
            }
        }
    }
}

void merge(struct person_t database[],int left,int right ,int size){
    
}

// void mergesort(struct person_t database[],int left,int right ,int size){
//     if  (right>left){
//         int mid = (left+right)/2;
//         mergesort(database,left,mid);
//         mergesort(database,mid+1,right);
//     }
//     else{
//         // merge
//     }
// }

int main(void){
    int size = 0;
    char cmd;
    do{
        int correctCmd = 0;
        char commands[] = {'i','p','h','r','s','m','b','d','q'};
        printf("Command: ");
        scanf(" %c",&cmd); 
        for (int i=0; i < strlen(commands);i++){
            if(commands[i]==cmd){
                correctCmd = 1;
            }
        }
        if(!correctCmd){
            printf("Invalid command '%c'\n",cmd);
        }
        else{
            if (cmd == 'i'){
                printf("Size? ");
                scanf(" %d",&size);
                initialise(persons,size);
            }
            else if(cmd == 'p'){
                printValues(persons,0,size);
            }
            else if(cmd == 'h'){
                float min = smallestElement(persons,size);
                float max = largestElement(persons,size);
                printf("Min: %.3f\nMax: %.3f\nRange: %.3f\n",min,max,max-min);
            }
            else if(cmd == 'r'){
                int index = 0;
                printf("Index? ");
                scanf(" %d",&index);
                replaceElement(persons,index,size);
            }
            else if(cmd == 's'){
                insertionsort(persons,size);
            }
        }
    }while(cmd != 'q');
    freeHeap(persons);
    printf("Bye\n");
    return 0;
}
