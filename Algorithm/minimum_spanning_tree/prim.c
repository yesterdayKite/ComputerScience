
#include <stdio.h>
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
 
int selected[MAX_VERTICES]; // 선택된 정점의 정보를 담을 배열, 선택이 됐는지 안됐는지를 표시한다.
int dist[MAX_VERTICES]; // 최소의 거리 정보만을 담는 배열, 새로운 최소거리가 나올 때마다 갱신된다.
 

void    print_selected_arr()
{
    printf("elected => ");
    for (int i = 0 ; i < MAX_VERTICES; i++)
    {
        printf("[%d] : %d / ", i, selected[i]);
    }
    printf("\n");
}


// 최소 dist[v]값을 갖는 정점을 반환
int get_min_vertex(int n)
{
  int v, i; // 정점의 정보를 저장할 변수 v, 반복문을 위한 변수 i
    
    v = 0;
    
  for (i = 1; i < n; i++)
    {
      if (selected[i] == FALSE) {
        v = i;  // 아직 선택되지 않은 정점의 번호를 v에 저장, 각 함수 실행별 0부터 n - 1까지 차례대로 저장
        break;
      }
    }
   
    // 위에서 선택된 정점이 최소거리를 지니고 있는 정점인지를 확인
    for (i = 0; i < n; i++)
    {
      // 선택되지 않은 정점들을 순회하면서 최소거리를 가진 정점을 찾음
      if ((selected[i] == FALSE) && (dist[i] < dist[v]))
        v = i;  // 더 적은 거리가 존재한다면 해당 정점을 저장
  }
    
  return(v);  // 최소의 거리를 갖는 정점이 선택됐으므로 정점 번호를 리턴
}
 



// Prim, s는 시작 정점
void prim(int s, int n)
{
  int i, u, v;
 
  for (u = 1; u < n; u++)  // dist배열과 selected배열의 정보를 초기화
  {
    dist[u] = INF;
    selected[u] = FALSE;
  }
  
    //selected[0] = TRUE;
    dist[s] = 0;  // 시작정점과 시작정점간의 거리는 0이다. 자기자신을 순환하는 경로는 없다고 가정.
   
  for (i = 0; i < n; i++)
  {
    print_selected_arr();
    // 리턴된 정점 번호를 u에 저장한다. u는 최소거리를 가지는 정점. 손으로 쓸때 선택하는 것과 같음
    u = get_min_vertex(n);
    selected[u] = TRUE; // 최소거리를 갖는 정점의 정보(u)를 알아냈으니 해당 정점을 선택했다고 표시한다.
 
    printf("*********  방문정점 : %d  *********\n\n\n", u+1); // 방문한 정점(u)을 출력한다.
 
    for (v = 0; v < n; v++)  // 이 과정은 새롭게 발견한 정보를 저장하는 과정이다.
    // 직접적인 경로가 발견되어 INF 에서 상수거리로 바뀌는 과정과
    // 기존의 상수거리보다 더 짧은 거리가 발견되 그 정보를 갱신하는 과정이 포함되어 있다.
    {
      // 선택된 u 정점을 기준으로 정점(u)과 연결되어 있는 정점까지의 거리를 각각 비교한다.
      if (weight[u][v] != INF)  // 정점 u와 연결이 되어있고
      {
        // 아직 선택되지 않았으며 해당 변(weight[u][v])의 길이가 기존의 dist[v] 값보다 작다면
        if (selected[v] == FALSE && weight[u][v] < dist[v])
          dist[v] = weight[u][v]; // dist[v]의 값을 갱신해준다.
        // 새롭게 발견되는 정점들이 초반에 저장될 수 있는 건 INF를 1000으로 설정해줬기 때문이다.
        // 우리가 만든 그래프의 경로값들은 전부 100이하의 값이기 때문에 새롭게 발견되는 정점이 있다면
        // 우선 등록되고 그 후 더 짧은 거리가 등장하면 갱신되는 형태로 이 프로그램은 작동한다.
      }
    }
  }
}
 
int main()
{
    prim(0, MAX_VERTICES);  // 정점 개수가 8개인 그래프에서 0번 정점을 출발하여 얻을 수 있는 최소비용신장트리를 찾아라.
    return 0;
}
 
