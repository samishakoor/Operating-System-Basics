#include "head.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void sort(int arr[], int n, int order)
{

    if (order == 0)
    {
        for (int i = 1; i < n; i++)
        {
            int tmp = arr[i];
            int j = i - 1;

            while (tmp < arr[j] && j >= 0)
            {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = tmp;
        }
    }
    else if (order == 1)
    {
        for (int i = 1; i < n; i++)
        {
            int tmp = arr[i];
            int j = i - 1;

            while (tmp > arr[j] && j >= 0)
            {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = tmp;
        }
    }
    else
    {
        printf("Please enter appropriate input\n");
    }
}
void findHighest(int arr[], int position, int n, int order)
{
    int highest=0;
    if (order == 0)
    {
       highest = arr[n-position];        
       printf("The %d highest number is %d \n",position,highest);
    }
    else if (order == 1)
    {
       highest = arr[position-1];
       printf("The %d highest number is %d \n",position,highest);
    }
    else
    {
        printf("Please enter appropriate input\n");
    }
}
void display(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
