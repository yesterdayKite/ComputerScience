#include <stdio.h>

void    print_array(int a[], int start, int end)
{
    for (int i = start ; i <= end ; i++)
    {
        printf("%d   ",a[i]);
    }
    printf("\n");
}

/*
 * 배열 A[p...r]의 원소들을 A[r]을 기준으로 양쪽으로 재배치하고, A[r]이 자리한 위치를 리턴한다.
 */
void    change_element(int *a, int *b)
{
    int     tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int    partition(int   A[], int p, int r)
{

    int i, j;
    i = p;
    j = p;
    
    if (p == r-1)
    {
        if (A[j] > A[r])
        {
            change_element(&A[r], &A[j]);
            print_array(A, 0, 7);


        }
        return (j);
    }
    
    while (j <= r)
    {
        if (A[j] > A[r])
        {
            j++;
        }
        else
        {
            change_element(&A[i++], &A[j++]);
            print_array(A, 0, 7);

        }
    }

    return (i+p-1);
}

void    quickSort(int   A[], int p, int r)
{
    int     q;
    
    if (p<r)
    {
        q = partition(A, p, r); // 분할
        print_array(A, 0, 7);
        quickSort(A, p, q-1); //왼쪽 부분 배열 정렬
        quickSort(A, q+1, r); // 오른쪽 부분 배열 정렬
    }
}

int main(){
    
    
    int A[] = {12, 70, 30, 20, 55, 25, 40, 50};
    printf("before sort : ");
    print_array(A, 0, 7);
    quickSort(A, 0, 7);
    printf("after sort : ");
    print_array(A, 0, 7);
    
    return 0;
}
