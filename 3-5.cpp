#include<iostream>
#include<thread>
#include<mutex>
#include<semaphore.h>
using namespace std;

#define MAX 10

int n;
sem_t forks[MAX];
mutex print_mtx;

void philosopher(int id)
{
    int left = id;
    int right = (id + 1) % n;

    for(int i=0;i<2;i++)
    {
        print_mtx.lock();
        cout<<"Philosopher "<<id<<" is THINKING\n";
        print_mtx.unlock();

        if(id % 2 == 0)
        {
            sem_wait(&forks[left]);
            sem_wait(&forks[right]);
        }
        else
        {
            sem_wait(&forks[right]);
            sem_wait(&forks[left]);
        }

        print_mtx.lock();
        cout<<"Philosopher "<<id<<" is EATING\n";
        print_mtx.unlock();

        sem_post(&forks[left]);
        sem_post(&forks[right]);
    }
}

int main()
{
    cout<<"Enter number of philosophers: ";
    cin>>n;

    thread ph[MAX];

    for(int i=0;i<n;i++)
        sem_init(&forks[i], 0, 1);

    for(int i=0;i<n;i++)
        ph[i] = thread(philosopher, i);

    for(int i=0;i<n;i++)
        ph[i].join();

    for(int i=0;i<n;i++)
        sem_destroy(&forks[i]);

    return 0;
}
