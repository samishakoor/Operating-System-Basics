#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// function to sort the elements of the array
void insertionSort(int arr[], int n) {
  for (int i = 1; i < n; i++) {
    int tmp = arr[i];
    int j = i - 1;

    
    while (tmp < arr[j] && j >= 0) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = tmp;
  }
}

void display(int arr[], int n) {     
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}



int main(int argc, char *arg[])
{
 // int arr[] = {6, 5, 1, 4, 3};


int arr[10];

for(int i=0 ; i<10 ;i++)
{
arr[i]=atoi(arg[i+1]);
}

  int n = sizeof(arr) / sizeof(arr[0]);
  printf("Elements before sorting:\n");
  display(arr, n);
  insertionSort(arr, n);
  printf("Elements after sorting:\n");
  display(arr, n);
 
   return 0;
}