#include <iostream>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

void *fibonachi_generator(void *param)
{
    int n = *((int *)param);    
    int first = 0, second = 1;
    int sum = 0;

    int *ptr = new int[n];
    ptr[0] = first;
    ptr[1] = second;

    int i = 2;
    sum = first + second;
    while (sum <= n)
    {
        ptr[i++] = sum;
        first = second;
        second = sum;
        sum = first + second;
    }

     ptr[i] = -1;

    pthread_exit((void*)ptr);
}

int main(int arg, char *argc[])
{
    int N = arg - 1;
    pthread_t my_thread[N];

    int *return_ptr = new int[N];
    
    for (int id = 0; id < N; id++)
    {
        int argument = atoi(argc[id + 1]);
        if(pthread_create(&my_thread[id], NULL, &fibonachi_generator, (void *)&argument)!=0)
        {
            cout << "pthread_create() failed !" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            pthread_join(my_thread[id],(void **)&return_ptr);
        }
        
        cout << "Thread " << id << ": ";
        for (int i = 0; return_ptr[i] != -1; i++)
        {
            cout << return_ptr[i] <<" ";
        }
        cout<<endl;
    }

    delete(return_ptr);
    pthread_exit(NULL);
    return 0;
}
