# include <stdio.h>

void    init_hash_table(int arr[], int len) //hash table 원소를 모두 -1로 초기화
{
    for (int i = 0 ; i < len ; i++)
        arr[i] = -1;
    return;
}




void    print_result(int arr[], int arr_len, int num1, int num2, int num3, int num4) //지정된 원소를 출력
{
    for (int i = 0 ; i <arr_len ; i++)
    {
        if(arr[i] == num1)
            printf("%d의 저장 인덱스 : %d\n", num1, i);
        else if(arr[i] == num2)
            printf("%d의 저장 인덱스 : %d\n", num2, i);
        else if(arr[i] == num3)
            printf("%d의 저장 인덱스 : %d\n", num3, i);
        else if(arr[i] == num4)
            printf("%d의 저장 인덱스 : %d\n", num4, i);
        else    {}
    }
}

void    print_arr(int arr[], int len) // 현재 배열 모든 원소 출력
{
    printf("___cur___\n");
    for (int i = 0 ; i < len ; i++)
        if(arr[i] == -1)
            printf("| [%d]   |\n", arr[i]);
        else
            printf("| [%d] %d |\n", i, arr[i]);
    printf("---------\n");
    printf("\n\n");
}

int power(int base, int index)
{
    int res = 1;
    
    if (index == 0) return 1;
    
    for (int i = 1 ; i <= index ; i++)
    {
        res *= base;
    }
    
    return res;
}

int main ()
{
    
    int idx;
    int cur_input;
    int j_tmp = 0; //충돌이 일어났을때 2의 지수가 될 수
    
    int int_input[] = {10, 20, 30, 40, 33, 46, 50, 60};
    int hash_table[13];
    
    init_hash_table(hash_table, 13); //hash table의 빈 원소를 모두 -1로 초기화한다.
    
    for (int i = 0 ; i < 8 ; i++)
    {
        cur_input = int_input[i];
        idx = cur_input%13;
        
        
        if(hash_table[idx] == -1) // 삽입하려는 원소가 비어있을 경우
        {
            hash_table[idx] = cur_input;
            printf("idx : %d 에 %d 삽입\n", idx, cur_input);
            print_arr(hash_table, 13);
        }
        else // 이미 삽입하려는 원소가 hash table에 차있을 경우, 이차원 조사
        {
            do{
            j_tmp++;
            printf("%d번째가 차있네요\n", idx);
            printf("%d에서", idx);
            printf("%d만큼 더 뛰어볼께요!\n", power(2, j_tmp));
            } while (hash_table[(idx + power(2, j_tmp))%13] != -1);
            
            
            hash_table[(idx+power(2, j_tmp))%13] = cur_input; //조사 완료한 곳에 삽입
            printf("idx : %d 에 %d 삽입\n", (idx+power(2, j_tmp))%13 , cur_input);
            print_arr(hash_table, 13);
        }
    }
        
        print_result(hash_table, 13, 33, 46, 50, 60);

        return 0;
        
}
    
    
    
    



