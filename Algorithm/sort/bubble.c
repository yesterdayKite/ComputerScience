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


void    change_element(int *a, int *b)
{
    int tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void    bubbleSort(int A[], int n)
{
    int     cnt = 1;
    for (int i = n ; i > 1 ; i--)
    {   
        for (int j = 0 ; j < i ; j++)
        {
            if ( A[j] > A[j+1] )
            {
                change_element(&A[j], &A[j+1]);
                print_array_cnt(A, 6, cnt);
                cnt++;
            }
        }
    }
}




int main(){
    
    int a[] = {12, 70, 30, 20, 55, 25};
    printf("before sort : ");
    print_array(a, 6);
    bubbleSort(a, 5);
    printf("after sort : ");
    print_array(a, 6);
    return 0;
}
