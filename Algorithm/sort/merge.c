
#include <stdio.h>
#include <stdlib.h>



void    print_array(int a[], int start, int end)
{
    for (int i = start ; i <= end ; i++)
    {
        printf("%d   ",a[i]);
    }
    printf("\n");
}

void    merge(int A[], int p, int q, int r)
{
    int     *B;
    int     t, i, j;
    
    i = p;
    j = q+1;
    t = p;
    B = (int*)malloc(sizeof(int)*(r - p + 1));
    
    while (t <= r)
    {
        if (t == r)
        {
            B[t++] = (i<j) ? A[i] : A[j];
            break;
        }
        if(A[i] <= A[j])
            B[t++] = A[i++];

        else
            B[t++] = A[j++];
    }
    for (int x = p ; x <= r ; x++)
        A[x] = B[x];
    }


void    mergeSort(int A[], int p, int r)
{
    int q = r;
    

    if (p < r)
    {
        q =  (int)((p+q)/2);

        mergeSort(A, p, q);
        mergeSort(A, q+1, r);
        merge(A, p, q, r);
        print_array(A, 0, 7);

    }
}

int main(){
    
    int A[] = {12, 70, 30, 20, 55, 25, 40, 50};
    printf("before sort : ");
    print_array(A, 0, 7);
    mergeSort(A, 0, 7);
    printf("after sort : ");
    print_array(A, 0, 7);
    return 0;
}
