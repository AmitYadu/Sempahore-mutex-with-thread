#include<iostream>
using namespace std;
class Queue
{
    public:
        int front,rear,size,capacity;
        int * array;
};
Queue* createqueue(int capacity)
{
    Queue* queue = new Queue();
    queue->capacity=capacity;
    queue->front=queue->rear=0;
    
    queue->rear = capacity -1;
    queue->array = new int[(capacity * sizeof(int))];
    return queue;
}
int isfull(Queue* queue)
{
    return (queue->size == queue->capacity);
}
int isempty(Queue* queue)
{
    return (queue->size==0);
}
void enqueue(Queue * queue,int item)
{
    if(isfull(queue))
    {
        return;
    }
    queue->rear = (queue->rear+1)%queue->capacity;
    queue->array[queue->rear]=item;
    queue->size = queue->size + 1;
}
int dequeue(Queue* queue)
{
    if(isempty(queue))
    {
        return -1;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)%queue->capacity;
    queue->size = queue->size-1;
    return item;
}
void printQ(Queue* queue)
{
    int j;
    for(int i = 0;i<queue->size;i++)
    {
        j = (queue->front+i)%queue->capacity;
        cout<<queue->array[j]<<" ";
    }
    cout<<"\n";
    return;
}