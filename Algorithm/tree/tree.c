
 # include <stdio.h>

char    node[9]= {'a','b','c','d','e','f','g','h','i'};
char    parent[9] = {'a', 'a', 'c', 'd', 'd', 'f', 'f', 'f', 'f'};
int     rank[9] = {1, 0, 0, 1, 0, 1, 0, 0, 0 };


int     Find_Node_Index(char c) //해당 문자의 node배열에서의 index를 알려준다.
{
    int     i = 0;
    while (node[i] != c){
        i++;
    }
    return i;
}


char    Find_Set(char   c) //노드 c가 포함된 트리의 루트를 리턴한다.
{
    int    found_index = Find_Node_Index(c);
    
    if (c == parent[found_index])
        return c;
    else
        return Find_Set(parent[found_index]);
}

void    union_set(char  x, char y){ // 노드 x가 속한 집합과 노드 y가 속한 집합을 합친다.
    char    x_parent = Find_Set(x);
    char    y_parent = Find_Set(y);
    
    if(rank[Find_Node_Index(x_parent)] > rank[Find_Node_Index(y_parent)]){
        parent[Find_Node_Index(y_parent)] = x_parent;
    }

    else {
        parent[Find_Node_Index(x_parent)] = y_parent;
        if (rank[Find_Node_Index(x_parent)] ==  rank[Find_Node_Index(y_parent)])
            rank[Find_Node_Index(y_parent)]++;
    }
}

void    print_all()
{
    printf("parent : ");
    for (int i = 0 ; i < 9 ; i++)
        printf("%c  ", parent[i]);
    printf("\n");
    
    printf("mark   : ");
    for (int i = 0 ; i < 9 ; i++)
        printf("%d  ", rank[i]);
    printf("\n");
    
    printf("node   : ");
    for (int i = 0 ; i < 9 ; i++)
        printf("%c  ", node[i]);
    printf("\n\n\n");

}

int main(){
    
    printf("===========first init=============\n");
    print_all();
    printf("===========after union (a)=============\n");
    union_set('b', 'c');
    print_all();
    printf("===========after union (b)=============\n");
    union_set('e', 'g');
    print_all();
    printf("===========after union (a) & (b)=============\n");
    union_set('a', 'f');
    print_all();
    
    
    
    return 0;
}

