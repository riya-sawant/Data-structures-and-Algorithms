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
//typedef for coordinates


int PX;
int PY;
//the coordinates x and y


//pointer for output
FILE * output;
coordinate * ReadData(int n);

void merge(coordinate Array[], int l, int mid, int a);
void mergeSort(coordinate Array[], int l, int a, int t);
void insertionSort(coordinate Array[], int l, int a);
void sort(coordinate Array[], int length, int threshold);
int compareTo(coordinate * ptrPt1, coordinate * ptrPt2);
int binarySearch(coordinate Array[], coordinate pointCoord, int l, int a);
void printArray(coordinate Array[], int n);

int main() 
{
    //atexit(report_mem_leak);
    //variables
    int n;
    int s;
    int t;

    //scaning in point x & y
    scanf("%d", &PX);
    scanf("%d", &PY);

    //scanning in threshold,monsters and searches
    scanf("%d", &n);
    scanf("%d", &s);
    scanf("%d", &t);

    //pointer for array, and setting that to readdata function
    coordinate * Array = ReadData(n);
    //allocating space pointcoordinate
    coordinate * pointCoords = malloc(sizeof(coordinate) * s);
    
    //gooing to be doing the search first for x and y
    for(int i = 0; i < s; i++)
        scanf("%d %d", &pointCoords[i].x, &pointCoords[i].y);   
    

    // from the search seeing the distance
    for(int i = 0; i < s; i++)
    {
        int x1 = pow((pointCoords[i].x - PX), 2);
        int x2 = pow((pointCoords[i].y - PY), 2);
        pointCoords[i].distance = x1 + x2;
    }
    //passing thru functions sort and printarray
    sort(Array, n, t);
    printArray(Array, n);
    
    //for the search distance we want to bass to binary search
    //binary will be going through and finind match
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



void merge(coordinate Array[], int l, int mid, int a)
{
    
    int sizeLeft = mid - l + 1;
    int sizeRight = a - mid;

    //allocating me moery for left and right sides
    coordinate * L = malloc(sizeLeft * sizeof(coordinate));
    coordinate * R = malloc(sizeRight * sizeof(coordinate));
    
    //we will be checking the left anmd right side of array to break down a match
    for(int i =  0; i < sizeLeft; i++)
        L[i] = Array[i + l];
    for(int j = 0; j < sizeRight; j++)
        R[j] = Array[j + mid + 1];
    int i = 0;
    int j = 0;
    int k = l;
    //calculating for left and comparing 
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
    //seeing if less than or equal to threshold, if so pass to insertion sort
    if((a - l + 1) <= t)
    {
        insertionSort(Array, l, a + 1);
    }
    else if (l < a)
      {
        //viewing with middle
        int mid = l + (a - l) / 2;

        mergeSort(Array, l, mid, t);
        mergeSort(Array, mid + 1, a, t);
        merge(Array, l, mid, a);
      }
}
void insertionSort(coordinate Array[], int l, int a)
{
    //from the merge sort function we want to insert in place with the rest of the  coordinates,checking with the other values, and saving them
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
  //passing array, lenght and thrshold and sending it through merge sort, to put them in place
  mergeSort(Array, 0, length - 1, threshold);
}

int compareTo(coordinate * ptrPt1, coordinate * ptrPt2)
{
    //comparing the coordinates and seeing the values if bigger/ equal to or less than, and storing them.
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
    //if location isless than or equal to mid previous value
    if(l <= a)
    {
        int mid = l + (a - l) / 2;
        //comparing with middle, and sorting it in the array, with less than 0, -1, greater than 0
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
  //we want output to be in a txt file
    output = fopen("out.txt", "w");
    //printing out the array coordinates 
    for(int i = 0; i < n; i++)
      printf("%d %d\n", Array[i].x, Array[i].y);
    for(int i = 0; i < n; i++)
      //keeping it in output
      fprintf(output, "%d %d\n", Array[i].x, Array [i].y);
    fclose(output);
}

coordinate * ReadData(int n)
{  
    
    coordinate * Coords = malloc(sizeof(coordinate) * n);
    
    //for the number of monsters we will be going through the coodinates
    for(int i = 0; i < n; i++)
        scanf("%d %d", &Coords[i].x, &Coords[i].y);
        
    
    for(int i = 0; i < n; i++)
    {
        int x1 = pow((Coords[i].x - PX), 2);
        int x2 = pow((Coords[i].y - PY), 2);
        //saving coordinates
        Coords[i].distance = x1 + x2;
    }
   
    return Coords;
}