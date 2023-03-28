#include <iostream>
#include <semaphore.h>
#include <string.h>

#include <sys/shm.h>
using namespace std;

sem_t *sem1 = new sem_t(); // semaphore 1
sem_t *sem2 = new sem_t(); // semaphore 2
sem_t *sem3 = new sem_t(); // semaphore 3

int N = 10;
int count = N;

void *function(void *param)
{
    int id = *(int *)param;

    sem_wait(sem1);
    cout << "This Is thread Number: " << id << endl;
    count--;
    sem_post(sem3);
    sem_post(sem1);

    if (count == 0)
    {
        while (N > 0)
        {
            cout << "Barrier crossed by thread Number: " << N << endl;
            N--;
        }
        sem_post(sem2);
    }

    pthread_exit(NULL);
}

int main(int arg, char *argc[])
{

    sem_init(sem1, 0, 1); // sem1=1
    sem_init(sem2, 0, 0);
    sem_init(sem3, 0, 1);

    pthread_t my_thread[N];

    for (int id = 0; id < N; id++)
    {
        sem_wait(sem3);
        pthread_create(&my_thread[id], NULL, &function, (void *)&id);
    }

    sem_wait(sem2);
    cout << "All threads have completed" << endl;
    return 0;
}