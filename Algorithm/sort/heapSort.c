#include <stdio.h>

void    print_array(int a[], int start, int end)
{
    for (int i = start ; i <= end ; i++)
    {
        printf("%d   ",a[i]);
    }
    printf("\n");
}

void    change_element(int *a, int *b)
{
    int     tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
}
/*
void    buildHeap(int   A[], int    n)
{
    for (int i = 1 ; i < n ; i++)
    {
        int child = i;
        while (child > 0)
        {
            int root = (int)((child-1)/2);
            if (A[root] < A[child])
                change_element(&A[root], &A[child]);
            child = root;
        }
    }
}

void    heapify(int   A[], int  start, int    n)
{
    for (int i = 1 ; i < n ; i++)
    {
        int child = i;
        while (child > 0)
        {
            int root = (int)((child-1)/2);
            if (A[root] < A[child])
                change_element(&A[root], &A[child]);
            child = root;
        }
    }
}
*/

void heapify(int arr[], int here, int size) {
    print_array(arr, 0, 7);

    int left = here * 2 + 1;
    int right = here * 2 + 2;
    int max=here;
    if (left<size&&arr[left]>arr[max])
        max = left;
    if (right < size&&arr[right]>arr[max])
        max = right;
 
    if (max != here) {
        change_element(&arr[here], &arr[max]);
        heapify(arr, max, size);
    }
}


void buildHeap(int arr[], int size) {
    int i;
    for (i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, i, size);
    }
}

void    heapSort(int    A[], int   n)
{
    buildHeap(A, n);
    for ( int i = n-1 ; i >= 0 ; i--)
    {
        change_element(&A[0], &A[i]);
        print_array(A, 0, 7);
        heapify(A, 0, i);
        print_array(A, 0, 7);

    }
}

int main(){
    
    
    int A[] = {12, 70, 30, 20, 55, 25, 40, 50};
    printf("before sort : ");
    print_array(A, 0, 7);
    heapSort(A, 7);
    printf("after sort : ");
    print_array(A, 0, 7);
    return 0;
}
