#include<iostream>
#include<string>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

int N=10;
sem_t semaphore1;
sem_t semaphore2;
sem_t semaphore3;

void* function(void* param)
{
	int id=* (int*)param;
	cout<<"Thread No: \t"<<id<<endl;
	if(id>=N)		
		sem_post(&semaphore2);
	else
		sem_post(&semaphore1);
		
	sem_wait(&semaphore2);
	
	cout<<"Barrier crossed by thread Number: \t"<<id<<endl; //this line will not be printed until all N threads have executed the first cout statement.
	
	N--;
	if(N==0);
		//sem_post(&semaphore3);
	else
		sem_post(&semaphore2);
}


int main()
{
	cout<<"started\n";
	sem_init(&semaphore1, 0, 1);
	sem_init(&semaphore2, 0, 0);
	sem_init(&semaphore3, 0, 0);
	pthread_t id[N];
	int i=0;
	while(i<N)
	{

		sem_wait(&semaphore1);
		pthread_create(&id[i], NULL, &function, (void*)&i);
		i++;
	}
	//sem_wait(&semaphore3);
	cout<<"Threads completed\n";
	return 0;

}

