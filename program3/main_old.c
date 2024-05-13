/* COP 3502C Programming Assignment 3 
This program is written by: Riya Sawant */ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "leak_detector_c.h"
//You must use a specified combination of Merge Sort and Insertion Sort to sort the point data. Specifically,

//merge, merge , sort, read data, binary

typedef struct coordinates
{
    int x;
    int y;
    int distance;

}coordinate;

int PX;
int PY;

FILE * output;
coordinate * ReadData(int n);

void merge(coordinate Array[], int l, int mid, int a);
void mergeSort(coordinate Array[], int l, int a, int t);
void insertionSort(coordinate Array[], int l, int a);
void sort(coordinate Array[], int length, int threshold);
int compareTo(coordinate * ptrPt1, coordinate * ptrPt2);
int binarySearch(coordinate Array[], coordinate pointCoord, int l, int a);
void printArray(coordinate Array[], int n);

int main() {

    // memory leak check
    //atexit(report_mem_leak);
    
    int n;
    int s;
    int t;
    
    scanf("%d", &PX);
    scanf("%d", &PY);
    
    scanf("%d", &n);
    scanf("%d", &s);
    scanf("%d", &t);

    coordinate * Array = ReadData(n);
    coordinate * pointCoords = malloc(sizeof(coordinate) * s);
    
  
    for(int i = 0; i < s; i++)
        scanf("%d %d", &pointCoords[i].x, &pointCoords[i].y);   
    

  
    for(int i = 0; i < s; i++)
    {
        int xC = pow((pointCoords[i].x - PX), 2);
        int xY = pow((pointCoords[i].y - PY), 2);
        pointCoords[i].distance = xC + xY;
    }
  
    sort(Array, n, t);
    printArray(Array, n);
    
  
    for(int i = 0; i < s; i++)
    {
        int res = binarySearch(Array, pointCoords[i], 0, n - 1);
        if(res == -1)
            printf("%d %d not found\n", pointCoords[i].x, pointCoords[i].y);
        else
            printf("%d %d found at rank %d\n", pointCoords[i].x, pointCoords[i].y, res + 1);
    }

    
    free(Array);
    free(pointCoords);
    
    return 0;
}

coordinate * ReadData(int n)
{
    coordinate * mCoords = malloc(sizeof(coordinate) * n);
    
    
    for(int i = 0; i < n; i++)
        scanf("%d %d", &mCoords[i].x, &mCoords[i].y);
        
    
    for(int i = 0; i < n; i++)
    {
        int xC = pow((mCoords[i].x - PX), 2);
        int xY = pow((mCoords[i].y - PY), 2);
        mCoords[i].distance = xC + xY;
    }
   
    return mCoords;
}



void merge(coordinate Array[], int l, int mid, int a)
{
    
    int sizeLeft = mid - l + 1;
    int sizeRight = a - mid;

  
    coordinate * L = malloc(sizeLeft * sizeof(coordinate));
    coordinate * R = malloc(sizeRight * sizeof(coordinate));
    
  
    for(int i =  0; i < sizeLeft; i++)
        L[i] = Array[i + l];
    for(int j = 0; j < sizeRight; j++)
        R[j] = Array[j + mid + 1];
    int i = 0;
    int j = 0;
    int k = l;
    
    while(i < sizeLeft && j < sizeRight)
    {
        if(compareTo(&L[i], &R[j]) < 0)
        {
            Array[k] = L[i];
            i++;
        }
        else
        {
            Array[k] = R[j];
            j++;
        }
        
        k++;
    }
    while(i < sizeLeft)
    {
        Array[k] = L[i];
        i++;
        k++;
    }
    while(j < sizeRight)
    {
        Array[k] = R[j];
        j++;
        k++;
    }
  
    free(L);
    free(R);
     
}

void mergeSort(coordinate Array[], int l, int a, int t)
{
    if((a - l + 1) <= t)
    {
        insertionSort(Array, l, a + 1);
    }
    else if (l < a)
      {
      
        int mid = l + (a - l) / 2;

        mergeSort(Array, l, mid, t);
        mergeSort(Array, mid + 1, a, t);
        merge(Array, l, mid, a);
      }
}
void insertionSort(coordinate Array[], int l, int a)
{
    int j;
    for(int i = l; i < a; i++)
    {
        
        coordinate hand = Array[i];
        
        for(j = i - 1; j >= l; j--)
        {
            if(compareTo(&hand, &Array[j]) < 0)
                Array[j + 1] = Array[j];
            else
                break;
        }
        
        Array[j + 1] = hand;
    }
}

void sort(coordinate Array[], int length, int threshold)
{
  
  mergeSort(Array, 0, length - 1, threshold);
}

int compareTo(coordinate * ptrPt1, coordinate * ptrPt2)
{

    if(ptrPt1->distance != ptrPt2->distance)
        return ptrPt1->distance - ptrPt2->distance;
    
    if(ptrPt1->x != ptrPt2->x)
        return ptrPt1->x - ptrPt2->x;
    
    if(ptrPt1->y != ptrPt2->y)
        return ptrPt1->y - ptrPt2->y;

    
    return 0;
}


int binarySearch(coordinate Array[], coordinate pointCoord, int l, int a)
{
    
    if(l <= a)
    {
        int mid = l + (a - l) / 2;

        if(compareTo(&Array[mid], &pointCoord) == 0)
            return mid;
        if(compareTo(&Array[mid], &pointCoord) > 0)
            return binarySearch(Array, pointCoord, l, mid - 1);
        else if(compareTo(&Array[mid], &pointCoord) < 0)
            return binarySearch(Array, pointCoord, mid + 1, a);
    }
   
    return -1;
}



void printArray(coordinate Array[], int n)
{
    output = fopen("out.txt", "w");
    for(int i = 0; i < n; i++)
      printf("%d %d\n", Array[i].x, Array[i].y);
    for(int i = 0; i < n; i++)
      fprintf(output, "%d %d\n", Array[i].x, Array [i].y);
    fclose(output);
}