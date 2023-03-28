#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    sort(arr, n, atoi(arg[11]));
    printf("Sorted Array: ");
    display(arr, n);

    findHighest(arr, atoi(arg[12]), n, atoi(arg[11]));

    return 0;
}