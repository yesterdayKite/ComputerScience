
# include <stdio.h>
# include <stdlib.h>
# define INF 9999
# define MIN(a, b) (((a) < (b)) ? (a) : (b))

void    print_D(int **D)
{
    int n = 7;
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            printf("%d  ",D[i][j]);
        }
        printf("\n");
    }
    
}

int**   init_2_dim_arr(int  n)
{
    int**   arr = (int**)malloc(sizeof(int*)*n);
    for (int i = 0 ; i < n ; i++)
    {
        arr[i] = (int*)malloc(sizeof(int)*n);
    }
    return arr;
}

void    print_2_dim_arr(int **arr, int row, int col)
{
    printf("\n");
    for (int i = 0 ; i < row ; i++)
    {
        for (int j = 0 ; j < col ; j++)
        {
            printf("%d   ",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    
}

void   zero_all_arr(int**    arr, int n)
{
    
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0; j < n ; j++)
        {
            arr[i][j] = 0;
        }
    }
    
}

int**    floyd(int W[][7], int**    D, int**    P)
{
    int n = 7;
    
    
    //D 초기화 : D를 W와 같은 원소로 채워넣는다.
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            D[i][j] = W[i][j];
        }
    }
    
    for (int k = 0 ; k < n ; k++)
    {
        for(int i = 0 ; i < n ; i++)
        {
            for (int j = 0 ; j < n ; j++)
            {
                if ( (D[i][k] + D[k][j] ) < D[i][j])
                {
                    P[i+1][j+1] = k+1;
                    D[i][j] = D[i][k] +D[k][j];
                }
            }
        }
    }
    return D;
    
}

void    path(int   **P, int    q, int  r) //재귀로 경로를 찾는 함수
{
    if (P[q][r] != 0)
    {
        path(P, q, P[q][r]);
        printf("A%d  -> ", P[q][r]);
        path(P, P[q][r], r);
    }
}

int main () {
    
    int **D;
    int **P;
    
    int W[7][7] = {{0, INF, INF, 8, INF, INF,INF},{10, 0, INF, INF, INF, INF, INF},{INF, INF, 0, 1, 12, INF, INF},{5, 19, 2, 0, 15, 5, INF},{INF, INF, INF, INF, 0, 6, INF},{INF, INF, INF, 18, INF, INF, 3},{INF, 10, INF, INF, INF, 4, 0}};

    
    D = init_2_dim_arr(7);
    P = init_2_dim_arr(8); //경로출력 편의를 위해 0행, 0렬을 쓰지 않는다.
    
    zero_all_arr(P, 7);
    

    D = floyd(W, D, P); //Floyd를 이용하여 D에 최단거리를 입력
    
    
    printf("===========D==========\n");
    print_2_dim_arr(D, 7, 7);
    printf("===========P==========\n");
    print_2_dim_arr(P, 8, 8);

    printf("A5에서 A2까지의 경로 : A5 -> ");
    path(P, 5, 2);
    printf("A2\n\n");
    return 0;
}


