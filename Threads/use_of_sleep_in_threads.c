#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int run_now = 1;

void *thread_function(void *arg)
{
    int print_count2 = 0;
   while (print_count2++ < 20)
    {
        printf("\nstart of thread\n");
        printf("print_count1 of thread: %d\n ",print_count2-1);
        if (run_now == 2)
        {
            printf("i am 2 of thread");
            printf("\n");
            run_now = 1;
        }
        else
        {
            printf("Run now of thread : %d\n ",run_now);
            sleep(1);
        }
           printf("\nend of thread\n");
    }
    pthread_exit(NULL);
}
int main()
{
    int res;
    pthread_t a_thread;
    res = pthread_create(&a_thread, NULL, &thread_function, NULL);
    int print_count1 = 0;
    while (print_count1++ < 20)
    {
        printf("\nstartof parent\n");
        printf("print_count1 of parent: %d\n ",print_count1-1);
        if (run_now == 1)
        {
            printf("i am 1 of parent");
            printf("\n");
            run_now = 2;
        }
        else
        {
            printf("Run now of parent : %d\n ",run_now);
            sleep(1);
        }
        printf("\nend of parent\n");
    }
    printf("Waiting for thread to finish...\n");
    pthread_join(a_thread, NULL);
    printf("Thread joined, it returned \n");
    exit(0);
}
