#include <stdio.h>
#include <stdarg.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int     subset_cnt = 0;

// 모든 subset의 경우를 행렬에 저장해두었다. ex) 23 = {V2, V3}, 124 = {V1, V2, V4}
int     first_v_subsets[] = {2,3,4,1,3,4,1,2,4,1,2,3};
int     second_v_subsets[] = {23, 24, 34, 13, 14, 34, 12, 14, 24, 12, 13, 23};
int     third_v_subsets[]= {234,134, 124, 123};



int     min(int n1, int n2, int n3) //3개 숫자를 비교하여 최솟값 리턴
{
    int     min;
    
    if (n1 <= n2)
        min = n1;
    else
        min = n2;
    if (n3 <= min)
        min = n3;
    return min;
}



int combination(int a, int b){ // nCr 을 리턴한다. (subset의 갯수 예측)
    int i, j, n=1, r=1;
    for(i=a; i>=a-b+1; i--)
        n=n*i;
    for(j=b; j>=1; j--)
        r=r*j;
    
    return(n/r);
    
}


//traeling salesman problem을 DP를 이용하여 해결

void    travel(int  n, int      D[][500], int    W[][5])
{
    int subset, subset_1, subset_2, subset_3;
    int subset_cnt;
    
    printf("\n\n=====================1단계===========================\n\n"); // 0으로 가는 모든 weight들을 주어진 배열을 바탕으로 초기화

    for (int i = 1 ; i <= n-1 ; i++){
        D[i][0] = W[i][0];
        printf("D[%d][0] = W[%d][1] = %d\n", i, i, W[i][0]);
    }

    printf("\n\n");

    for (int i = 1 ; i <= n-2 ; i++)
    {
        subset_cnt = 0;
        printf("\n\n\n=====================%d단계===========================\n\n", i+1);
        for (int k = 1; k<= n-1 ; k++) // 총 n-1 만큼의 반복한다.
        {

            for (int j = 0 ; j < combination(n-2, i) ; j++) // 나올수 있는 subset의 수 만큼 반복하므로 nCr 만큼 반복한다.
            {
                //첫번재, 두번째, 세번째 반복할때마다 덧셈 수가 달라지므로, if문을 통하여 분기하였다.
                
                if (i == 1)
                {
                    subset = first_v_subsets[subset_cnt++];
                    D[k][subset] = W[k][subset] + D[subset][0];
                    printf("D[V%d][{V%d}] = %d + %d = %d\n", k, subset, W[k][subset],D[subset][0],D[k][subset]);
                }
                else if (i == 2)
                {
                    //subset의 원소들을 각각 subset_1, subset2 에 저장
                    subset = second_v_subsets[subset_cnt++];
                    subset_2 = subset % 10;
                    subset_1 = ((subset - subset_2)/10);
                    
                    D[k][subset] = MIN((W[k][subset_1]+D[subset_1][subset_2]), (W[k][subset_2]+D[subset_2][subset_1]));
                    printf("D[V%d][{V%d, V%d}] = min(W[V%d][{V%d}]+D[V%d][{V%d}],W[V%d][{V%d}]+D[V%d][{V%d}]) = min(%d + %d , %d + %d) = %d\n\n" , k, subset_1, subset_2, k, subset_1, subset_1, subset_2, k, subset_2, subset_2, subset_1, W[k][subset_1], D[subset_1][subset_2], W[k][subset_2], D[subset_2][subset_1] ,D[k][subset] );
                    
                }
                else if (i == 3)
                {
                    //subset의 원소들을 각각 subset_1, subset2, subset3 에 저장
                    subset = third_v_subsets[subset_cnt++];
                    subset_1 = subset / 100;
                    subset_3 = subset % 10;
                    subset_2 = (subset - subset_1*100 - subset_3)/10;
                                        
                    D[k][subset] =  min((W[k][subset_1]+D[subset_1][subset-subset_1*100]), (W[k][subset_2]+D[subset_2][subset_1*10+subset_3]), (W[k][subset_3]+D[subset_3][subset/10]));
                    printf("D[V%d][{V%d, V%d, V%d}] = min(W[V%d][{V%d}]+D[V%d][{V%d, V%d}], W[V%d][{V%d}]+D[V%d][{V%d, V%d}], W[V%d][{V%d}]+D[V%d][{V%d, V%d}]) = min(%d, %d, %d) = %d \n", k, subset_1, subset_2, subset_3, k, subset_1, subset_1, subset_2, subset_3, k, subset_2, subset_2, subset_1, subset_3, k, subset_3, subset_3, subset_1, subset_2,(W[k][subset_1]+D[subset_1][subset-subset_1*100]), (W[k][subset_2]+D[subset_2][subset_1*10+subset_3]), (W[k][subset_3]+D[subset_3][subset/10]), D[k][subset] );
                }
                else {
                    ;
                }
            }
        }
    }
}


int main ()
{
    int W[5][5] = {{0,8,13,18,20},
                    {3,0,7,8,10},
                    {4,11,0,10,7},
                    {6,6,7,0,11},
                    {10,6,2,1,0}};
    int D[5][500];
    
    
    travel(5, D, W);
    
    printf("\n\n=====================5단계===========================\n");
    printf("\nD[V1][{V2, V3,V4, V5}] \n= min(W[1][2]+D[2][{V3, V4 , V5 }], W[1][3]+D[3][{V2 , V4 , V5 }], W[1][4]+D[4][{V2 , V3 , V5}], W[1][5]+D[5][{V2 , V3 , V4 }])");
    printf("\n = min(%d+%d , %d+%d , %d+%d , %d+%d) = %d \n\n\n", W[0][1], D[1][234], W[0][2], D[2][134], W[0][3], D[3][124], W[0][4], D[4][123], (W[0][1]+D[1][234]) );
    printf("최단거리 : 1 -> 2 -> 3 -> 4 -> 5 \n\n\n");
    
    return 0;
}

