#include <stdio.h>
#include <stdlib.h>
# define INF 9999

void    print_3dim_arr(int***  D)
{
    int n = 7;
    
    for (int i = 0 ; i < n ; i++)
    {
        printf("=========D^%d번째 행렬==========\n", i);
        for (int j = 0 ; j < n ; j++)
        {
            for (int k = 0 ; k < n ; k++)
                printf("%d  ", D[i][j][k]);
            printf("\n");
        }
        printf("\n\n\n");

    }
}

int***    simpleShortestPath1(int*** D, int W[][7])
{
    int n = 7;
    int tmp_min = INF;
    int fin_min = INF;
    
    
    //D 초기화 : D를 W와 같은 원소로 채워넣는다.
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            D[0][i][j] = W[i][j];
        }
    }
    
    for (int m = 1 ; m < n ; m++)
    {
        print_3dim_arr(D);

        for (int i = 0 ; i < n ; i++)
        {
            for (int j = 0 ; j < n ; j++)
            {
                for (int k = 1 ; k < n ; k++)
                {
                    tmp_min = D[m-1][i][k] + W[k][j];
                    if (tmp_min <= fin_min){
                        fin_min = tmp_min;
                    }
                }
                D[m][i][j] = fin_min;
                tmp_min = INF;
                fin_min = INF;
            }
        }
    }
    return D;
    
}


int***      init_3dim_arr(void)
{
    int n = 7;
    
    int ***D = (int***)malloc(sizeof(int**)*n);
    
    for (int i = 0 ; i < n ; i++)
    {
        D[i] = (int**)malloc(sizeof(int*)*n);
        for (int j = 0 ; j < n; j++)
        {
            D[i][j] = (int*)malloc(sizeof(int)*n);
            for (int k = 0 ; k < n ; k++)
            {
                D[i][j][k] = 0;
            }
        }
    }

    return D;
}

int main () {
    
    int*** D;
    
    int W[7][7] = {{INF, 4, INF, INF, INF, 10, INF},{3, INF, INF, 18, INF, INF, INF},{INF, 6, INF, INF, INF, INF, INF},{INF, 5, 15, INF, 2, 19, 5},{INF, INF, 12, 1, INF, INF, INF},{INF, INF, INF, INF, INF, INF, 10},{INF, INF, INF, 8, INF, INF, INF}};

    
    D = init_3dim_arr();
    D = simpleShortestPath1(D, W);

    print_3dim_arr(D);

    
    return 0;
}


