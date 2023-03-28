#include <iostream>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

void *worker_thread1(void *list)
{

    int *arr = (int *)list;

    int sum = 0;
    int count = 0;
    for (int i = 0; arr[i] != -1; i++)
    {
        sum += arr[i];
        count++;
    }

    float *average = new float;
    *average = sum / (count);

    pthread_exit((void *)average);
}

void *worker_thread2(void *list)
{
    int *arr = (int *)list;

    int max = arr[0];
    int i;
    for (i = 1; arr[i] != -1; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    int *maximum = new int;
    *maximum = max;
    pthread_exit((void *)maximum);
}

void *worker_thread3(void *list)
{
    int *arr = (int *)list;

    int min = arr[0];
    int i;
    for (i = 1; arr[i] != -1; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    int *minimum = new int;
    *minimum = min;
    pthread_exit((void *)minimum);
}

int main(int arg, char *argc[])
{
    int N = arg - 1;
    int list[N + 1];
    int i;
    for (i = 0; i < N; i++)
    {
        list[i] = atoi(argc[i + 1]);
    }
    list[i] = -1;

    pthread_t my_thread1;
    pthread_t my_thread2;
    pthread_t my_thread3;

    float *return_arg = new float;
    int *max = new int;
    int *min = new int;

    cout << "The main Thread will print :" << endl;

    if (pthread_create(&my_thread1, NULL, &worker_thread1, (void *)list) != 0)
    {
        cout << "pthread_create() failed !" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        pthread_join(my_thread1, (void **)&return_arg);
        cout << "The average value is : " << *return_arg;
    }

    cout << endl;

    if (pthread_create(&my_thread2, NULL, &worker_thread2, (void *)list) != 0)
    {
        cout << "pthread_create() failed !" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        pthread_join(my_thread2, (void **)&max);
        cout << "The maximum value is : " << *max;
    }

    cout << endl;

    if (pthread_create(&my_thread3, NULL, &worker_thread3, (void *)list) != 0)
    {
        cout << "pthread_create() failed !" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        pthread_join(my_thread2, (void **)&min);
        cout << "The minimum value : " << *min;
    }
    cout << endl;

    return 0;
}
