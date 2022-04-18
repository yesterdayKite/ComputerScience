# include<stdio.h>
# include<stdlib.h>

struct _node{
    struct _node *next;
    int     data;
}typedef s_node;

void    init_hash_table(s_node *arr[], int  table_len) //hash table 의 원소를 모두 NULL로 초기화
{
    for (int i = 0 ; i< table_len ; i++)
        arr[i] = NULL;
}

void    print_all(s_node    *arr[], int table_len) //hash table의 모든 원소를 출력
{
    s_node      *cur_ptr;
    
    printf("---table-----\n");
    for (int i = 0 ; i< table_len ; i++)
    {
        if (arr[i] == NULL)
            printf(" [%d]    \n", i);
        else
        {
            cur_ptr = arr[i];
            while(cur_ptr != NULL)
            {
                printf(" [%d] %d   ", i, cur_ptr->data);
                cur_ptr = cur_ptr -> next;
            }
            printf("\n");
        }
        
    }
    printf("\n\n");
}


void    print_result(s_node **arr, int   table_len, int   num1, int num2, int num3, int num4)
{
    s_node      *cur_ptr;

    for (int i = 0 ; i < table_len ; i++)
    {
        if (arr[i] != NULL)
        {
            cur_ptr = arr[i];

            while(cur_ptr != NULL)
            {
                if ((cur_ptr->data) == num1)
                    printf("%d의 저장 인덱스 : %d\n", cur_ptr->data, i);
                else if ((cur_ptr->data) == num2)
                    printf("%d의 저장 인덱스 : %d\n", cur_ptr->data, i);
                else if ((cur_ptr->data) == num3)
                    printf("%d의 저장 인덱스 : %d\n", cur_ptr->data, i);
                else if ((cur_ptr->data) == num4)
                    printf("%d의 저장 인덱스 : %d\n", cur_ptr->data, i);
                else   {}
                cur_ptr = cur_ptr -> next;
            }
        }
    }
    printf("\n\n");
}


int main ()
{
    int input_arr_len = 8;
    int int_input[] = {10, 20, 30, 40, 33, 46, 50, 60};
    int cur_input;
    int idx;
    
    s_node  **hash_table = malloc((sizeof(s_node *)*13));
    
    init_hash_table(hash_table, 13);
    
    for (int i = 0 ; i < input_arr_len ; i++)
    {
        cur_input = int_input[i];
        idx = cur_input%13;
        
        if(hash_table[idx] == NULL) // 삽입하려는 원소가 비어있을 경우
        {
            s_node  *new_node = malloc(sizeof(s_node)); //새로운 노드를 생성
            hash_table[idx] = new_node; //새로운 노드를 연결
            hash_table[idx]->data = cur_input;
            hash_table[idx]->next = NULL;
            printf("idx : %d 에 %d 삽입\n", idx, hash_table[idx]->data);
            print_all(hash_table, 13);
        }
        else //삽입하려는 원소에 linked list가 존재할 때
        {
            s_node  *new_node = malloc(sizeof(s_node)); //새로운 노드를 생성
            new_node -> data = cur_input;
            new_node -> next = hash_table[idx];
            hash_table[idx] = new_node; //새로운 노드를 연결
            
            printf("idx %d에 %d 삽입\n", idx, hash_table[idx]->data);
            print_all(hash_table, input_arr_len);
        }
    }
    
    
    print_result(hash_table, 13, 33, 46, 50, 60); // argument의 index를 출력
    
    return 0;
}
