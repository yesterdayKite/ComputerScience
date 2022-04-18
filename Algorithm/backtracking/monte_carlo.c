#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int input[6] = { 2, 10, 13, 17, 22, 42 }; //Input
int x[6] = { 0, }; //지난 node weight 값 저장하는 배열
int res = 0; //최종 값


int is_promising(int i, int weight, int total) { //promising한 노드인지 판별
   if (weight + total >= res && (weight == res || weight + input[i + 1] <= res)) {
      return 1; // promising
   }
   return 0; // not promising
}


void print_1dim_arr() { //res값에 해당하는 경로에 대한 x배열 출력
    int len = 6;
   for (int i = 0; i < len; i++) {
      if (x[i] != 0) {
         printf("-> %d ", x[i]);
      }}
   
   printf("\n");
}


void subset_res(int i, int weight, int result){
   if (is_promising(i, weight, result)) {
      if (res == weight) { //구하고자 하는 값과 동일할 때
         printf("답에 포함 : ");
          print_1dim_arr();
      }
      else {
         x[i + 1] = input[i + 1];
          subset_res(i + 1, weight + input[i + 1], result - input[i + 1]);
         x[i + 1] = 0;
          subset_res(i + 1, weight, result - input[i + 1]);
      }
   }
}

//몬테카를로 함수
int monte(){ //몬테카를로 함수

    int idx = 1;
    int weight = 0;
    int num;
    int total = 106;
    int check = 1;
    int promising_child_num = 2; //노드의 promising child  개수
    int mprod = 1; //promising child 개수의 곱을 갖는 변수
    int node_num = 1; //총 node의 개수
   
   
   srand((unsigned int)time(NULL)); //random 값 생성

   while (promising_child_num != 0) {
       promising_child_num = 0;
       check = 1;

      weight = weight + input[idx + 1];
      total = total - input[idx + 1];

      if (is_promising(idx + 1, weight, total)) {
          promising_child_num++;
          check = check * (-1);
      }

      weight = weight - input[idx + 1];
      if (is_promising(idx + 1, weight, total)) {
          promising_child_num++;
          check = check * 2;
      }
       
      mprod = mprod * promising_child_num;
       node_num = node_num + mprod * 2;
       num = (int)rand() % 2;
       
      if (check == -2) { //양쪽 다 유망한 노드일 때
         if (num) { //왼쪽노드
             idx++;
            weight = weight + input[idx];
         }
         else { //오른쪽 노드
             idx++;
         }
      }
      else if (check == 2) {
          idx++;
      }
      else if (check == -1) {
          idx++;
         weight = weight + input[idx];
      }
   }
   return node_num;
}

int main (){
    int total = 0;
    int result = 0;

    printf("============================\n");
    printf("input the num to search ::: ");
    scanf("%d", &res);
    
    for (int i = 0; i < 6; i++) total += input[i];
   
    subset_res(-1, 0, total);
    
    result = monte();
    printf("\n효율성 : %d\n", result);
    
    return 0;
}
   
