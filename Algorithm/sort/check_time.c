# include<stdio.h>
# include<stdlib.h>
# include <time.h>



void       print_arr(float  *arr, int num)
{
    for (int i = 0 ; i < num; i ++)
        printf("%.2f / ", arr[i]);
    printf("\n");
}

int    get_biggest(float a[], int length)
{
    float biggest;
    int biggest_index;
    
    biggest = a[0];
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

void    change_last(float a[], int length, int changing_index, int full_length)
{
    float tmp;


    tmp = a[length];
    a[length] = a[changing_index];
    a[changing_index] = tmp;
}

void    selectionSort(float *A, int n)
{
    int biggest_index;
        
    for (int i = n-1 ; i > 1 ; i-- )    {
        biggest_index = get_biggest(A, i);
        change_last(A, i, biggest_index, n);
    }
}


void    change_element(float *a, float *b)
{
    float tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
}


void    bubbleSort(float A[], int n)
{
    for (int i = n ; i > 1 ; i--)
    {
        for (int j = 0 ; j < i ; j++)
        {
            if ( A[j] >= A[j+1] )
            {
                change_element(&A[j], &A[j+1]);
            }
        }
    }
}


void    insertSort(float  A[], int    n)
{
    float     where_to_insert;
    int     j;
    
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
    }
}


void merge(float A[], int low, int mid, int high) {

    float   *B;
    int i = low;
    int j = mid+1;
    int k = low;

    B = (float*)malloc(sizeof(float)*(high-low+1));

    while (i<=mid && j<=high) {
        if(A[i] < A[j]) {
           B[k++] = A[i++];
        } else if(A[i] >= A[j]) {
           B[k++] = A[j++];
        }
    }
    // 남은 영역 조사후 mergedArr으로 복사

    if(i>=mid) {
        while(j<=high) {
           B[k++] = A[j++];
        }
    }

    if(j>=high) {
        while(i<=mid) {
           B[k++] = A[i++];
        }
    }
    for (int x = low ; x <= high ; x++)
        A[x] = B[x];
}



void mergeSort(float    *arr, int low, int high) {
    int mid;
    if(low < high) {
        mid = (low + high)/2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}


int getPivot(float data[], int start, int end) {
    int i = start -1, j;
    float   pivot = data[end], tmp;
    for(j = start; j<end; j++) {
        if(data[j] <= pivot) {
            tmp = data[++i];
            data[i] = data[j];
            data[j] = tmp;
        }
    }
    tmp = data[i+1];
    data[i+1] = data[end];
    data[end] = tmp;
    return i+1;
}

void quickSort(float data[], int start, int end) {
    if(start<end) {
        int pivot = getPivot(data, start, end);
        quickSort(data, start, pivot-1);
        quickSort(data, pivot+1, end);
    }
}


void heapify(float arr[], int here, int size) {

    int left = here * 2 + 1;
    int right = here * 2 + 2;
    int max=here;
    if (left<size && arr[left]>arr[max])
        max = left;
    if (right < size && arr[right]>arr[max])
        max = right;
 
    if (max != here) {
        change_element(&arr[here], &arr[max]);
        heapify(arr, max, size);
    }
}


void buildHeap(float arr[], int size) {
    int i;
    for (i = size / 2 - 1; i >= 0; i--)
    {
        heapify(arr, i, size);
    }
}

void    heapSort(float    A[], int   n)
{
    buildHeap(A, n);
    for ( int i = n-1 ; i >= 0 ; i--)
    {
        change_element(&A[0], &A[i]);
        heapify(A, 0, i);

    }
}

/*
void heapify(float *arr, int size){
    for(int i=1;i<size;++i){
        int child = i;
        do{
            //자식 노드가 부모 노드보다 크면 교환
            int root = (child-1)/2;
            if(arr[root]<arr[child]){
                float temp = arr[root];
                arr[root] = arr[child];
                arr[child] = temp;
            }
            child = root;
        }while(child!=0);    //최상단 노드까지 점검
    }
}

//최상단 노드와 최하단 노드 교체
void heap(float *arr, int *size){
    float temp = arr[0];
    arr[0] = arr[*size-1];
    arr[*size-1] = temp;
    --(*size);
}

void    heapSort(float *A, int n)
{
    int     size = n;
    
    for(int i=0;i<n;++i){
        heapify(A, size);
        heap(A, &size);
    }
}
*/
float*    get_random_arr(int    num)
{
    int     plus_or_minus;
    float *arr = (float*)malloc(sizeof(float)*num);

    for(int i = 0 ; i < num ; i++)
    {
        plus_or_minus = (rand()%9)>4 ? 1 : -1;
        float x = (float)(rand()%100)/100;
        arr[i] =  x * (float)plus_or_minus;
    }
    return arr;
}

float*     copy_arr(float   *old_arr, int   num)
{
    float *new_arr = (float*)malloc(sizeof(float)*num);
    
    for (int i = 0 ; i < num ; i++)
        new_arr[i] = old_arr[i];
    return new_arr;
}



int main ()
{
    float   *arr;
    float   *selection_arr;
    float   *bubble_arr;
    float   *insert_arr;
    float   *merge_arr;
    float   *quick_arr;
    float   *heap_arr;
    
    clock_t start, finish;
    double duration;
    
    //selection
    /*
    printf("================selection==============\n");
    for(int i = 1000 ; i <= 20000 ; i += 1000 )
    {
        arr = get_random_arr(i);
        selection_arr = copy_arr(arr, i);
        
        start = clock();
        selectionSort(selection_arr, i);
        finish = clock();
        duration = (double)(finish - start);
        printf("%d : %fms\n",i, duration);
    }
  
    printf("================bubble==============\n");
    for(int i = 1000 ; i <= 20000 ; i += 1000 )
    {
        arr = get_random_arr(i);
        bubble_arr = copy_arr(arr, i);
        
        start = clock();
        bubbleSort(bubble_arr, i-1);
        finish = clock();
        duration = (double)(finish - start);
        printf("%d : %fms\n",i, duration);
    }
     
    
    printf("================insert==============\n");
    for(int i = 1000 ; i <= 20000 ; i += 1000 )
    {
        arr = get_random_arr(i);
        insert_arr = copy_arr(arr, i);
        
        start = clock();
        insertSort(insert_arr, i);
        finish = clock();
        duration = (double)(finish - start);
        printf("%d : %fms\n",i, duration);
    }
     
    printf("================merge==============\n");
       for(int i = 1000 ; i <= 20000 ; i += 1000 )
       {
           arr = get_random_arr(i);
           merge_arr = copy_arr(arr, i);
           
           start = clock();
           mergeSort(merge_arr,0, i-1);
           finish = clock();
           duration = (double)(finish - start);
           printf("%d : %fms\n",i, duration);
       }
    
    
    printf("================quick==============\n");
       for(int i = 1000 ; i <= 20000 ; i += 1000 )
       {
           arr = get_random_arr(i);
           quick_arr = copy_arr(arr, i);
           
           start = clock();
           quickSort(quick_arr,0, i-1);
           finish = clock();
           duration = (double)(finish - start);
           printf("%d : %fms\n",i, duration);
       }
     
     */
    
    printf("================heap==============\n");
       for(int i = 1000 ; i <= 20000 ; i += 1000 )
       {
           arr = get_random_arr(i);
           heap_arr = copy_arr(arr, i);
           
           start = clock();
           heapSort(heap_arr,i);
           finish = clock();
           duration = (double)(finish - start);
           printf("%d : %fms\n",i, duration);
       }
    

    

    return 0;
}


