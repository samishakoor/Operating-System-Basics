#include <iostream>
#include <fstream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

using namespace std;


struct sum_count
{
int sum;
int count;
};

struct shared_portions
{
sum_count arr[2];
int curr_index;
float average;


shared_portions()
{
    arr[0].count=0;
    arr[1].count=0;
    arr[0].sum=0;    
    arr[1].sum=0; 
    curr_index=0;
    average=0;
}

};

int shm_id = shmget(51, 1024, IPC_CREAT | 0666 | IPC_EXCL);
shared_portions *shm = (shared_portions *)shmat(shm_id, NULL, 0);


sem_t *sem2=new sem_t();
sem_t *sem3=new sem_t();

void *thread1(void * param)
{

    sem_wait(sem2);
    ifstream file1;
    file1.open("array1.txt");
    int num=0;
    shm->curr_index=0;
    while(file1 >> num)
    {
        shm->arr[shm->curr_index].sum+= num;
        shm->arr[shm->curr_index].count++;
    }
   
    sem_post(sem3);

    pthread_exit(NULL);
}

void *thread2(void * param)
{
    sem_wait(sem3);
    ifstream file2;
    file2.open("array2.txt");
    int num=0;
    shm->curr_index=1;
    while(file2 >> num)
    {
        shm->arr[shm->curr_index].sum+= num;
        shm->arr[shm->curr_index].count++;
    }

    pthread_exit(NULL);
}

int main()
{
   
  
    int id_sem=shmget(61, 1024, IPC_CREAT | 0666 | IPC_EXCL);

    sem_t *semaphore=new sem_t();
    semaphore=(sem_t*)shmat(id_sem,NULL,0); 


    sem_init(semaphore, 1, 0);
    sem_init(sem2, 0, 1);
    sem_init(sem3, 0, 0);

    pthread_t p1,p2;
  
    pthread_create(&p1,NULL,&thread1,NULL);
    pthread_create(&p2,NULL,&thread2,NULL);


    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    


 char a;
 cout<<"Press any key to Start: ";
 cin>>a;
 
 sem_post(semaphore); 
 
 

 cout<<"Press any key to End: ";
 cin>>a;

  sem_destroy(semaphore);
  shmdt(semaphore);
  shmdt(shm);
  shmctl(id_sem, IPC_RMID, NULL);
  shmctl(shm_id, IPC_RMID, NULL);


    return 0;
}
