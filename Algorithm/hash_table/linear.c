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

int main ()
{
    
    int idx;
    int cur_input;
    
    int int_input[] = {10, 20, 30, 40, 33, 46, 50, 60};
    int hash_table[13];
    
    printf("hi");
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
        else // 이미 삽입하려는 원소가 hash table에 차있을 경우, 선형조사
        {
            idx++;
            while(hash_table[idx] != -1){idx++;}
            
            hash_table[idx] = cur_input; //선형조사 완료한 곳에 삽입
            printf("idx : %d 에 %d 삽입\n", idx, cur_input);
            print_arr(hash_table, 13);
        }
    }
        
        print_result(hash_table, 13, 33, 46, 50, 60);
        
        return 0;
        
}
    
    
    
    


