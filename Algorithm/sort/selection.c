#include<stdio.h>


int    get_biggest(int a[], int length)
{
    int biggest;
    int i;
    int biggest_index;
    
    i = 0;
    biggest =a[0];
    biggest_index = 0;
    
    for (int i = 0 ; i < length ; i++)
    {
        if (biggest <= a[i+1])
        {
            biggest = a[i+1];
            biggest_index = i+1;
        }
    }
    return biggest_index;
}

void    print_array(int a[], int length)
{
    for (int i = 0 ; i< length ; i++)
        printf("%d   ",a[i]);
    printf("\n");
}

void    print_array_cnt(int a[], int length, int cnt)
{
    printf("%d 번째 step : ", cnt);
    for (int i = 0 ; i< length ; i++)
        printf("%d   ",a[i]);
    printf("\n");
}

void    change_last(int a[], int length, int changing_index, int full_length)
{
    int tmp;


    tmp = a[length];
    a[length] = a[changing_index];
    a[changing_index] = tmp;
}


void    selectionSort(int *A, int n)
{
    int biggest_index;
    int cnt;
    
    for (int i = n-1 ; i > 1 ; i-- )
    {
        cnt = n-i;
        biggest_index = get_biggest(A, i);
        change_last(A, i, biggest_index, n);
        print_array_cnt(A, 8, cnt);
    }
}


int main(){
    int a[] = {12, 70, 30, 20, 55, 25};
    printf("before sort : ");
    print_array(a, 6);
    selectionSort(a, 6);
    printf("after sort : ");
    print_array(a, 8);
    return 0;
}

