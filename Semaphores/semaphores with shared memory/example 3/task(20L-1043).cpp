#include <iostream>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <semaphore.h>
#include<stdio.h>
#include <fstream>
using namespace std;

struct Buffer
{
  char buff[20];
  char ending_char;
};

int id = shmget(12345, 1024, IPC_CREAT | 0666);
int read_id= shmget(12345, 1024, 0);

// creating semaphores
sem_t *sem1 = new sem_t(); // semaphore 1
sem_t *sem2 = new sem_t(); // semaphore 2

void *producer_thread(void *arg)
{
  string f_name = *(string *)arg;
  ifstream in;
  in.open(f_name, ios::in);

  Buffer *shared_buffer = (Buffer *)shmat(id, NULL, 0);
  int count = 0;
  char c;
  int i = 1;

  while (!in.eof())
  {
    in.get(c);
    shared_buffer->buff[count] = c;
    count++;
    if (count * i == 20 * i)
    {
      sem_post(sem2);
      sem_wait(sem1);
      i++;
      count = 0;

      char a;
      cout<<endl;
      cout<<"Press any Key to continue.";
      cin>>a;
      cout<<endl;
    } 
  }
  pthread_exit(NULL);
}

void *consumer_thread(void *arg)
{

while(true)
{

   sem_wait(sem2);
   Buffer *read_shared_buffer = (Buffer *)shmat(read_id, NULL, 0);
   for (int i = 0; i < 20; i++)
   {
    cout<<read_shared_buffer->buff[i];
   }
   cout<<endl;
  sem_post(sem1);
}

  pthread_exit(NULL);
}

int main(int arg, char *argc[])
{

  int N = arg - 1;
  string file_name = argc[N];

  sem_init(sem1, 0, 0);
  sem_init(sem2, 0, 0);
  
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, producer_thread, (void *)&file_name);
  pthread_create(&tid2, NULL, consumer_thread, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  return 0;
}