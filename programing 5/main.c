//riya sawant
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "leak_detector_c.h"
#define MAXLEN 51
#define SIZE 100000

struct heapStruct
{
    char **heaparray;
    int capacity;
    int size;
};

struct heapStruct* initHeap(int size)
{
  struct heapStruct* h;
  h = (struct heapStruct*)(malloc(sizeof(struct heapStruct)));
  h->capacity = size;
  h->heaparray = (char**)malloc(sizeof(char*)*(size+1));
  h->size = 0;
  return h;
}

// prototypes
FILE *outtxt;
struct heapStruct *initHeap(int size);
int insert(struct heapStruct *h, char *value, int minOrMax);
void percolateUp(struct heapStruct *h, int index, int minOrMax);
void percolateDown(struct heapStruct *h, int index, int minOrMax);
char *removeRoot(struct heapStruct *h, int minOrMax);
int minimum(char *a, int indexOfA, char *b, int indexOfB);
int maximum(char *a, int indexOfA, char *b, int indexOfB);
int compareTo(char *str1, char *str2);
void printMedian(int n);
void swap(struct heapStruct *h, int index1, int index2);
void freeHeap(struct heapStruct *h);
void printHeap(struct heapStruct *h);

int main()
{
  outtxt = fopen("out.txt", "w");
  //memmory leak
  //atexit(report_mem_leak);
  //variables
  int n;
  //scanning in
  scanf("%d", &n);

  
  printMedian(n);
  //return n ;
  return 0;
}

void printHeap(struct heapStruct *h) {
    int i;
    for (i=1; i<=h->size; i++)
        printf("%s ", h->heaparray[i]);
    printf("\n");
}

void percolateUp(struct heapStruct *h, int index, int minOrMax)
{
  if (index > 1)
  {
    if (minOrMax == 1)
    {
      if (compareTo(h->heaparray[index/2], h->heaparray[index]) > 0)
      {
     
        swap(h, index, index/2);
        percolateUp(h, index/2, minOrMax);
      }
      }
        
      else
        {
        if (compareTo(h->heaparray[index/2], h->heaparray[index]) < 0)
          {
            swap(h, index/2, index);
            percolateUp(h, index, minOrMax);
          }
        }
    // }
  }
}   

void percolateDown(struct heapStruct *h, int index, int minOrMax)
{
  int minVal, maxVal;
  if ((2*index+1) <= h->size)
  {
    if(minOrMax == 1)
    {
      minVal = minimum(h->heaparray[2*index], 2*index, h->heaparray[2*index+1], 2*index+1);
      if (compareTo(h->heaparray[index], h->heaparray[minVal]) > 0)
      {
      swap(h, index, minVal);
      percolateDown(h, minVal, minOrMax);
      }
      else if (h->size == 2*index)
      {
        if (compareTo(h->heaparray[index], h->heaparray[2*index]) > 0)
          swap(h, index, 2*index);
      }
    }
    else{
      maxVal = maximum(h->heaparray[2*index], 2*index, h->heaparray[2*index+1], 2*index+1);
      if (compareTo(h->heaparray[index], h->heaparray[maxVal]) < 0)
      {
        swap(h, index, maxVal);
        percolateDown(h, maxVal, minOrMax);
      }
      else if(h->size == 2*index)
      {
        if (compareTo(h->heaparray[index], h->heaparray[2*index]) < 0)
          swap(h, index, 2*index);
      }
    }
  }
}

int insert(struct heapStruct *h, char *value, int minOrMax)
{
  
  if (h->size == h->capacity) 
  {
    h->heaparray = (char**)realloc(h->heaparray, sizeof(char*)*(2*h->capacity+1));
    
    if (h->heaparray == NULL)return 0;
    h->capacity *= 2;
  }
  h->size++;
  h->heaparray[h->size] = malloc(sizeof(char)*(MAXLEN));
  strcpy(h->heaparray[h->size], value);
  percolateUp(h, h->size, minOrMax);
  return 1;
}

void swap(struct heapStruct *h, int index1, int index2)
{
  char temp[MAXLEN];
  strcpy(temp, h->heaparray[index1]);
  strcpy(h->heaparray[index1], h->heaparray[index2]);
  strcpy(h->heaparray[index2], temp);
} 

int minimum(char *a, int indexOfA, char *b, int indexOfB)
{ 
  if (compareTo(a,b)< 0)return indexOfA;
  else return indexOfB;
}

int maximum(char *a, int indexOfA, char *b, int indexOfB)
{
  if(compareTo(a,b) > 0)
    return indexOfA;
  else
    return indexOfB;
}

void printMedian(int n)
{

  //struct heapStruct* smaller = init(n/2+1)
  //struct heapStruct* greater = inint(n/2+1)
  
  struct heapStruct *smaller, *greater;
  char str[MAXLEN];

  smaller = initHeap(n/2+1);
  greater = initHeap(n/2+1);
    //take in input
    // put in correct heap
    //print meadian
  //printf("STRING = %s", str);
  /*scanf("%s", str);
  //printf("STRING = %s", str);
  
  insert(smaller, str, 2);

  char median[MAXLEN];
  strcpy(median, str);
  
  printf("%s\n", str);
  fprintf(outtxt, "%s\n", str);*/
  char median[MAXLEN];
  strcpy(median, str);
  
  for(int i = 0;i < n; i++)
  {
    scanf("%s", str);
    //smaller->size > greater-> size
    //CASE1
    if(smaller->size > greater->size)
    {
      if(compareTo(str, median)< 0)
      {
        
        char *temp = removeRoot(smaller, 2);
        //AYOO
        //if (temp == NULL) printf("null");
        //exit(0);
        //printf("%s\n", temp);
        insert(greater, temp, 1);
        free(temp);
        insert(smaller, str, 2);
      }
        //else (compareTo >0)
      else 
      {
        insert(greater, str, 1);
        //insert (greater->size)
      }
      //printf(%s,%s);
      //strcpy (med, smaller->heapArray[1]);
      //printf("%s %s\n", smaller->heaparray[1], greater->heaparray[1]);
      fprintf(outtxt, "%s %s\n", smaller->heaparray[1], greater->heaparray[1]);
      strcpy(median, smaller->heaparray[1]);
      //printf("Case 1 smaller heap:");
  //printHeap(smaller);
  //printf("Case 1 greater heap:");
  //printHeap(greater);
    }

      //CASE 2
      //if (smaller->size == greater-> size)
    else if(smaller->size == greater->size)
    {


      //if  compTo(curr, med)<0
          //insert(smaller)
          //strcpy(med, smaller)
      if(compareTo(str, median)< 0)
      {
        insert(smaller, str, 2);
        strcpy(median, smaller->heaparray[1]);
        
      }
       //else (>0) 
      else
      {
        //insert into greater
        //set med to grreater root
        insert(greater, str, 1);
        strcpy(median, greater->heaparray[1]);
      }
      //printf median
      //printf("%s\n", median);
      fprintf(outtxt, "%s\n", median);
      //printf("Case 2 smaller heap:");
  //printHeap(smaller);
  //printf("Case 2 greater heap:");
  //printHeap(greater);
    }


      //CASE 3
      //if (smaller->size < greater-> size)
    else
    {
      //printf(" str = %s\t median = %s\n", str, median);
      if(compareTo(str, median)> 0)
      {
        
        
          //remove (smaller->size);
          //insert (greater->size, );
         // insert (smaller->size);
      
        char *temp = removeRoot(greater, 2);
        //insert(smaller, str, 2);
        insert(smaller, temp, 0);
        free(temp);
        insert(greater, str, 1);
      }
      else
      {
        insert(smaller, str, 1);
      }
      //printf(%s,%s);
      //strcpy (med, smaller->heapArray[1]);
      //printf("%s %s\n", smaller->heaparray[1], greater->heaparray[1]);
      fprintf(outtxt, "%s %s\n", smaller->heaparray[1], greater->heaparray[1]);
      //strcpy (med,smaller->heapArray[1]);
      strcpy(median, smaller->heaparray[1]);
      //printf("Case 3 smaller heap:");
  //printHeap(smaller);
  //printf("Case 3 greater heap:");
  //printHeap(greater);
    }
  }

  
  
  freeHeap(smaller);
  freeHeap(greater);
}

  
char *removeRoot(struct heapStruct *h, int minOrMax){//
  if (h->size > 0){
    char *removeVal = malloc(sizeof(char)*(strlen(h->heaparray[1]) + 1));
    strcpy(removeVal, h->heaparray[1]);
    strcpy(h->heaparray[1], h->heaparray[h->size]);
    free(h->heaparray[h->size]);
    h->size--;
    percolateDown(h, 1, minOrMax);
    return removeVal;
  }
  else
    return NULL;
}

int compareTo(char *str1, char *str2)
{
  //int length1 = strlen(str1);
  //int length2 = strlen(str2);
  //if(length1 != length2){
    //return length1 -length2;
  //}
  // rule 1 - return the word with the least characters
  // rule 2 - if str1 and str2 has the same # of chars, then return it alphabetically
  if(strlen(str1) < strlen(str2)) {
    return -1;
  } else {
    if(strlen(str1) > strlen(str2)) {
      return 1;
    } else {
     return strcmp(str1, str2);
    }
  }

    //return strcmp(str1, str2);
    
  }
    
  //return strcmp(str1, str2);



void freeHeap(struct heapStruct *h)
{
  for(int i = 1; i <= h->size; i++){
    free(h->heaparray[i]);
  }
  free(h->heaparray);
  free(h);
}