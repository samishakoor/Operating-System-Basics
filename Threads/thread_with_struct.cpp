#include <iostream>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

struct arguments
{
    char c;
    int n;
};

void *print_character(void *arg)
{

    struct arguments *obj = (struct arguments *)arg;

    char *ptr1 = new char;
    int *ptr2 = new int;

    *ptr1 = obj->c;
    *ptr2 = obj->n;

    int i = 0;
    while (i < *ptr2)
    {
        cout << *ptr1 << endl;
        i++;
    }
    pthread_exit(NULL);
}

int main()
{

    pthread_t t_id;

    char char_input;
    int no_of_times;
    
    cout << "Enter a character: ";
    cin >> char_input;
    cout << "Enter number of times you want to print character: ";
    cin >> no_of_times;
    cout << endl;
    
    if (no_of_times > 0)
    {
        struct arguments thread_var;
        thread_var.c = char_input;
        thread_var.n = no_of_times;
        if (pthread_create(&t_id, NULL, print_character, (void *)&thread_var) !=0)
        {
            cout << "pthread_create failed!" << endl;
             exit(EXIT_FAILURE);
        }
        pthread_join(t_id, NULL);
    }
    else
    {
        cout << "Incorrect input !" << endl;
    }
    return 0;
}
