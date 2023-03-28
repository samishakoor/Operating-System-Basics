#include <iostream>
using namespace std;
#include <semaphore.h>
#include <sys/shm.h>
#include <queue>
#include <string.h>

struct Student
{

 int rollNumber;
 char name[20];

};

int main()
{


   Student *buffer;

  int id_sem=shmget(1234, 1024, 0);
  int id_cs= shmget(5678, 1024,  0);

  sem_t *semaphore;
 
  if (id_sem==-1 || id_cs==-1)
  {
   
    cout<<"ERROR!";
    return 1;
    
  }




  semaphore= (sem_t*) shmat(id_sem, NULL, 0);
   buffer= (Student*) shmat(id_cs, NULL, 0);

  //sem_init(semaphore, 1, 1); //no need for this in client

  sem_wait(semaphore);

   cout<<buffer[0].rollNumber<<endl<<buffer[0].name<<endl;
 
 
 sem_post(semaphore); 
 


  shmdt(semaphore);
  shmdt(buffer);
  shmctl(id_sem, IPC_RMID, NULL);
  shmctl(id_cs, IPC_RMID, NULL);
}
