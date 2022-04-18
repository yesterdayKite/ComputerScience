#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
 
#define MAX_VERTICES 8  // 신장트리의 정점 개수
#define INF 9999 // 경로가 없는 INFINITE를 표현하기 위해 정의된 상수 INF
 


int weight[MAX_VERTICES][MAX_VERTICES] = {// 신장트리의 거리와 모양을 배열로 표현, INF는 바로갈 수 있는 경로가 없음을 뜻한다.
    {0, 11, 9, 8, INF, INF, INF, INF},
    {11, 0, 3, INF, 8, 8, INF, INF},
    {9, 3, 0, 15, INF, 12, 1, INF},
    {8, INF, 15, 0, INF, INF, 10, INF},
    {INF, 8, INF, INF, 0, 7, INF, 4},
    {INF, 8, 12, INF, 7, 0, INF, 5},
    {INF, INF, 1, 10, INF, INF, 0, 2},
    {INF, INF, INF, INF, 4, 5, 2, 0}
};

void    print_2dim_arr(int  **arr, int len){
    printf("========sorted_edges=========\n");
    printf("--weight---from--start--\n");

    for (int i = 0 ; i < len ; i++)
    {
        printf("%d           (%d -> %d)\n",arr[i][0], arr[i][1], arr[i][2]);
    }
    printf("\n\n\n\n");
}

void    print_1dim_arr(int*  arr, int len)
{
    printf("-------cycletable------\n");
    for (int i = 0 ; i < len ; i++)
        printf("%d    ", arr[i]);
    printf("\n");
}

void    bubble_sort(int **arr, int cnt)    // 매개변수로 정렬할 배열과 요소의 개수를 받음
{
    int* tmp;

    for (int i = 0; i < cnt; i++)    // 요소의 개수만큼 반복
    {
        for (int j = 0; j < cnt - 1; j++)   // 요소의 개수 - 1만큼 반복
        {
            if (arr[j][0] > arr[j + 1][0])          // 현재 요소의 값과 다음 요소의 값을 비교하여
            {                                 // 큰 값을
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;            // 다음 요소로 보냄
            }
        }
    }
}

int**   make_sorted_edges(){
    
    int     edge_num = 14;
    int     arr_len = 8;
    int     arr_cnt = 0;
    
    int     **arr = (int**)malloc(sizeof(int*)*edge_num);
    
    for(int i = 0 ; i < edge_num ; i++) //sorted edges들을 저장할 2차원 행렬 생성
    {
        arr[i] = (int*)malloc(sizeof(int)*3);
    }
    
    for (int i = 0 ; i < arr_len ; i++)
    {
        for (int j = i ; j < arr_len; j++)
        {
            //if ((weight[i][j] != INF) && (weight[i][j] != 0))
            if ((weight[i][j] != INF) && (weight[i][j] != 0))
            {
                arr[arr_cnt][0] = weight[i][j]; //첫번째 요소에 weight 저장
                arr[arr_cnt][1] = i; //두번째 요소에 i 값 (=출발 vertext) 저장
                arr[arr_cnt][2] = j; // 세번재 요소에 j값 (=도착 vertext) 저장
                arr_cnt++;
            }
        }
    }

    bubble_sort(arr, edge_num);
    
    print_2dim_arr(arr, edge_num);
    
    
    return arr;
}

int     check_cycle_table_all_true(int  *cycle_table, int   len) //cycle table이 모두 TRUE면 1, 하나라도 FALSE가 존재하면 0 리턴
{
    for (int i = 0 ; i < len ; i++)
    {
        if(cycle_table[i] == FALSE)
            return FALSE;
    }
    
    return TRUE;
    
}



void    kruskal(int   **arr, int  vertex_num, int edge_num)
{
    int     *cycle_table;
    
    cycle_table = (int*)malloc(sizeof(int)*vertex_num);
    
    for (int i = 0 ; i < edge_num ; i++) //cycle_table을 index와 동일한 내용으로 초기화
        cycle_table[i] = FALSE;
    
    
    
    for(int i = 0 ; i < edge_num ; i++){
        
        
        if ((cycle_table[arr[i][1]] == FALSE) || (cycle_table[arr[i][2]] == FALSE)){ //두 vertex가 모두 연결되있지 않아 false일때
            printf("%d - %d 연결\n", arr[i][1], arr[i][2]);
            cycle_table[arr[i][1]] = TRUE;
            cycle_table[arr[i][2]] = TRUE;
        }
        
        if(check_cycle_table_all_true(cycle_table, vertex_num)){//모든 vertex가 연결되어있으면 함수 종료
            printf("\n연결 완료!\n\n");
            return; //프로그램 종료
        }
        
    }
}


int main (){
    
    int **sorted_edges;
    int vertex_num = 8;
    int edge_num = 14;
    
    printf("======================================\n");
    printf("=============크루스칼 알고리즘=============\n");
    printf("======================================\n\n\n");

    
    sorted_edges = make_sorted_edges(); //정렬된 weight 와 from->start vertext를 담은 배열을 리턴한다.
    
    kruskal(sorted_edges, vertex_num, edge_num);
    
    
    return 0;
    
    
}


