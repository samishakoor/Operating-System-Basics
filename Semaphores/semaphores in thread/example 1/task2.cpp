#include <iostream>
using namespace std;
#include <semaphore.h>
#include <string.h>
#include <sys/shm.h>

//creating semaphores
sem_t *sem1;    //semaphore 1
sem_t *sem2;    //semaphore 2
sem_t *sem3;    //semaphore 3

void *thread1(void *arg) 
{
while(1)
{
  sem_wait(sem3);
    cout << "a";
  sem_post(sem1);
}

  pthread_exit(NULL);
}

void *thread2(void *arg) 
{

while(1)
{
  sem_wait(sem2);
    cout << "b";
  sem_post(sem3);
}


  pthread_exit(NULL);
}

void *thread3(void *arg) 
{

while(1)
{
  sem_wait(sem1);
    cout << "c";
  sem_post(sem2);
}
  pthread_exit(NULL);
}


int main() {

  sem_init(sem1, 0, 1);   //first semaphore is initialized to 1
  sem_init(sem2, 0, 0);   //second semaphore is initialized to 0
  sem_init(sem3, 0, 0);   //third semaphore is initialized to 0

  pthread_t tid1, tid2,tid3;

  pthread_create(&tid1, NULL, thread1, NULL);
  pthread_create(&tid2, NULL, thread2, NULL);
  pthread_create(&tid3, NULL, thread3, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  
  return 0;
}

