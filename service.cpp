#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include"queue.h"
using namespace std;
#define cnum 14

int Max= 7;
int service_time[cnum];
int Full = 0;
int Empty =Max;
int last = 0,flag=0,slept =0,front=0,rear =0;

sem_t mutex;
sem_t prod;
sem_t cons;

Queue* queue = createqueue(Max);

int random_number(int min,int max)
{
    return (rand() % (max - min + 1)) + min;
}

void* producer(void* arg)
{
    while(1)
    {
        sem_wait(&mutex);
        if(isfull(queue))
        {
            cout<<"Queue is full , custmer "<<*((int *)arg)<<" leaves"<<"\n\n";
            sleep(2);
            sem_post(&mutex);
            break;
        }
        else
        {
            enqueue(queue,*((int *)arg));
            cout<<"Queue: ";
            printQ(queue);
            cout<<"custumer "<<*((int *)arg)<<" is added to queue"<<"\n";
            sem_post(&cons);
            sem_post(&mutex);
            sem_wait(&prod);
            break;
        }
    }
}


void* service(void* arg)
{
    int item;
    while(true)
    {
        sem_wait(&cons);
        sem_wait(&mutex);
        item = dequeue(queue);
        cout<<"custmer "<<item<<" is serviced for "<<service_time[item-1]<<" sec by service personal number "<<*((int *)arg)<<" \n";
        sleep(service_time[item-1]*1);
        sem_post(&prod);
        sem_post(&mutex);
    }
}

int main()
{
    int choice =0;
    int z=0;    
    while(choice !=1 && choice != 2)
    {
        if(z==0)
        {
            cout<<"enter the number of personal required(1/2): "<<"\n";
            cin>>choice;
            cout<<"\n";
            z=1;
        }
        else 
        {
            cout<<"please enter valid number of service personal:"<<"\n";
            cin>>choice;
            cout<<"\n";
        }
    }   
    for(int i=0;i<cnum;i++)
    {
    service_time[i] = random_number(1,5);
    }
    sem_init(&mutex,0,1);
    sem_init(&prod,0,0);
    sem_init(&cons,0,0);

    switch(choice)
    {
    case 1:
    {
        cout<<"servicing with single personal"<<"\n";
        int a=1;
        int s[cnum];
        for(int i=1;i<=cnum;i++)
        {
            s[i-1] = i;
        }
        pthread_t personal,customer[cnum];
        cout<<"custmer 1 arrive and wakeup service personal "<<"\n\n";

        pthread_create(&personal, NULL, service, (void *)&a);
        for(int i=0;i< cnum;i++)
        {
        pthread_create(&customer[i], NULL,producer, (void *)&s[i]);

        }
        pthread_join(personal, NULL);
        for(int i=0;i<cnum;i++)
        {
            pthread_join(customer[i],NULL);
        }
        break;

    }
    case 2:
    {
        cout<<"servicing with two personal"<<"\n";
        int a[2]={1,2};
        int s[cnum];
        for(int i=1;i<=cnum;i++)
        {
            s[i-1] = i;
        }
        pthread_t personal[2],customer[cnum];
        cout<<"custmer 1 arrive and wakeup service personal "<<"\n\n";
        for(int i=0;i<2;i++)
        {
        pthread_create(&personal[i], NULL, service, (void *)&a[i]);

        }
        for(int i=0;i< cnum;i++)
        {
        pthread_create(&customer[i], NULL,producer, (void *)&s[i]);

        }
        for(int i=0;i<2;i++)
        {
        pthread_join(personal[i], NULL);

        }
        for(int i=0;i<cnum;i++)
        {
            pthread_join(customer[i],NULL);
        }
        break;
       


    }

    }





    

    return 0;
}
