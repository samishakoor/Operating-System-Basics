#include <iostream>
#include <fstream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>
#include <string>
#include <vector>
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


int main()
{
    
 
    int shm_id = shmget(51, 1024, 0);
    shared_portions *shm = (shared_portions *)shmat(shm_id, NULL, 0);

    int id_sem=shmget(61, 1024, 0);
    sem_t *semaphore=new sem_t();
    semaphore=(sem_t*)shmat(id_sem,NULL,0); 

    sem_wait(semaphore);
    shm->average=(shm->arr[0].sum+shm->arr[1].sum)/(shm->arr[0].count+shm->arr[1].count);
    cout << "Average is: " << shm->average << endl;
    sem_post(semaphore);
 
    return 0;
}