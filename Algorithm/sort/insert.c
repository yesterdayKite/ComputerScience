#include <stdio.h>


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

void    insertSort(int  A[], int    n)
{
    int     where_to_insert;
    int     j;
    int     cnt;
    
    cnt = 1;
    where_to_insert = 0;
    
    for (int i = 1 ; i < n ; i++)
    {
        where_to_insert = A[i];
        
        for (j = i-1 ; j >= 0 ; j--)
        {
            if (A[j] > where_to_insert)
                A[j+1] = A[j];
            else
                break;
        }
        A[j+1] = where_to_insert;
        print_array_cnt(A, 8, cnt++);

    }
}


int main(){
    
    int a[] = {12, 70, 30, 20, 55, 25, 40, 50};
    printf("before sort : ");
    print_array(a, 8);
    insertSort(a, 8);
    printf("after sort : ");
    print_array(a, 8);
    return 0;
}
