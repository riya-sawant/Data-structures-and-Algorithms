struct heapStruct
{
    char **heaparray;
    int capacity;
    int size;
};


//function prototypes
struct heapStruct *initHeap(int size);
void percolateUp(struct heapStruct *h, int index, int minOrMax);

//struct Student getMaxAverageStudent(struct Student *s, int n); 

//void readData(struct Student *students, int *c)