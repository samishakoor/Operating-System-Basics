#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "head.h"
#include "func.c"

int main(int argc, char *arg[])
{
    int arr[10];

    for (int i = 0; i < 10; i++)
    {
        arr[i] = atoi(arg[i + 1]);
    }

    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array Elements: ");
    display(arr, n);

    int order=atoi(arg[11]);
    sort(arr,n,order);
    printf("Sorted Array: ");
    display(arr, n);


    int position=atoi(arg[12]);
    
    findHighest(arr,position,n,order);

    return 0;
}
