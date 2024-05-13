// Riya Sawant-CS1-COP
//hi
//in.txt
//gcc main.c 
//
//./a.out <in.txt
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "leak_detector_c.h"

const int MAXNAMESIZE = 15;
//#define CONSTANT int
const int MAXITEMS = 100;
const int timeperitem = 5;
const int timepercustomer = 30;
const int maxtime = 100000000;
// You must dynamically allocate memory as appropriate for linked lists.
typedef struct customer 
{
    char name [MAXNAMESIZE + 1];
    int ntickets;
    int linenum;
    int timeenter;

} customer;
// You must create a node struct for a linked list of customers. This struct
// should have a pointer
// to a customer struct, and a pointer to a node struct.
typedef struct node 
{
    customer *customerPtr;
    struct node *next;
} customerPtr;
// You must create a struct to store a queue of customers. This struct should
// have two pointers – one to the front of the queue and one to the back.
typedef struct storeQue 
{
    struct node *front;

    struct node *back;

} storeQue; 
//
struct customer *createCustomer(char* name, int timeenter, int linenum, int ntickets);
void initqueue (struct storeQue* qPTR);
int timeUsed(int ntickets, struct customer *temp);
void enqueue(struct storeQue* qPTR, customer *createCustomer);
struct customer* dequeue(struct storeQue* qPTR);
int empty(struct storeQue* qPTR);
struct customer * peek(struct storeQue* qPTR);
int getNext(struct storeQue* qPTR, int currentTime,int linenum);
void freememory(customer* createCustomer,int temp);


struct customer *createCustomer(char* name, int timeenter, int linenum, int ntickets)
{
    char custname[MAXNAMESIZE + 1];
    struct customer* generateCustomer = malloc(sizeof(customer));
    
    scanf("%d %d %s %d", &timeenter, &linenum, custname, &ntickets);
    
    generateCustomer->timeenter = timeenter;
  
    generateCustomer->linenum = linenum;

    generateCustomer->ntickets = ntickets;
    
    strcpy(generateCustomer->name, custname);
    
    return generateCustomer;
}


int getNext(struct storeQue* qPTR, int currentTime,int linenum)
{
    
    int res = -1,minTickets = MAXITEMS + 1;

    for(int i = 0; i < 12; i++)
    {
        
          if(empty(&qPTR[i])) continue;
        
        customer *temp = peek (&qPTR[i]);
        if(temp->timeenter >= currentTime) continue;


        
           if(temp->ntickets< minTickets) 
          {
          res = i;
          
          minTickets = temp->ntickets;
          
          }
    }

    if(res != -1) return res;

    
    int bestTime =MAXITEMS + 1;

    for(int i = 0; i < 12; i++)
    {
      
      if(empty(&qPTR[i])) continue;
      customer *temp = peek(&qPTR[i]);

            if (res <0)
            {
          
          res = i;
          temp->timeenter < bestTime;
          bestTime = temp->timeenter;
        
            }
      }
  
return res;
}

void initqueue (struct storeQue* qPTR)
{
  // set queuePtr(front & back) = NULL
  //front->NULL
  //back->NULL
    qPTR->front = NULL;
    qPTR->back = NULL;
}
//--------------------------
void enqueue(struct storeQue* qPTR, customer* createCustomer)
{
    struct node * temp;
    temp = malloc(sizeof(struct node));

  
    temp->customerPtr = createCustomer;
    temp->next = NULL;

  
    if(qPTR->back != NULL)
      qPTR->back->next = temp;
    


    qPTR->back = temp;

    if(qPTR->front == NULL)
    qPTR->front = temp;
    
}


struct customer * dequeue(struct storeQue* qPTR)
{


    customer *holder;
    holder = qPTR->front->customerPtr;


  
    struct node *temp;
    temp = qPTR->front;

  
    qPTR->front = qPTR->front->next;
    return holder;


  
    if(qPTR->front == NULL)
    {
        qPTR->back = NULL;
        //return NULL;
    }

}

struct customer *peek(struct storeQue* qPTR)
{
  if (empty(qPTR))return NULL;
  return qPTR->front->customerPtr;
}


int empty(struct storeQue* qPTR)
// returns 1 if the queue is empty, 0 if it is not)
// return Ptr-> front = NULL $
{
    if (qPTR->front == NULL)
    {
      // if EMPTY
      return 1;
    }
    else
    {
      //printf("not empty");
      // if NOT empty
      return 0;
    }
    
}
int timeUsed(int ntickets, struct customer *temp)
{

return ((temp->ntickets) * timeperitem) + timepercustomer;

}




void freememory(customer *createCustomer,int temp)

{
    
    {
        free(createCustomer);
        free(temp);
    }
  
}

int main() 
{
    
    //atexit(report_mem_leak); 

    
    customer * oneCustomer;
    int timeenter;
    int linenum; 
    int ntickets;
    int nCustomers; 
    int testCases;
    int currentTime;
    //char custname[MAXNAMESIZE + 1];
    char *name;

    name = NULL;


    scanf("%d", &testCases);
    for(int t = 0; t < testCases; t++){
     
        int currentTime = 0;
        scanf("%d", &nCustomers);

        struct storeQue Qs[12];

        for(int i = 0; i < 12; i++)
        {
        initqueue (&Qs[i]);
        }

      
        for(int i = 1; i <=nCustomers ; i++)
        {     
            oneCustomer = createCustomer(timeenter, name, linenum, ntickets);
            for(int j = 0; j <= 12; j++)
            {
                
                if(oneCustomer->linenum == j)enqueue(&Qs[j-1],oneCustomer);
                
              
                if(empty(&Qs[j]) == 1)continue;
                
            }
        }

    
        
      int savegetnx = getNext(Qs, currentTime, linenum);
        
      
      while(savegetnx != -1)
        {
            struct customer * temp = dequeue(&Qs[savegetnx]);

            //MATH AND PRINT
            if(currentTime < temp->timeenter)
            {
                currentTime = temp->timeenter;
            }
            currentTime += timeUsed(ntickets,temp);
          
            printf("%s from line %d checks out at time %d.\n", temp->name, temp->linenum, currentTime);
                /////////////////////  
              savegetnx = getNext(Qs,linenum,currentTime);

          
        }
    }

  return 0;
}
