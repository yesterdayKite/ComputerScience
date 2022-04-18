#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 20


int front = -1;
int rear = -1;
int queue[20];
 
typedef struct  _node{
    struct _node    *leftChild;
    struct _node    *rightChild;
    int     history[10];
    int     profit;
    int     weight;
    int     bound;
}Node;

int table[5][3] = {{20, 2, 10}, {30, 5, 6}, {35, 7, 5}, {12, 3, 4}, {3, 1, 3}};
int W = 9;

/*
 queue 이용 관련 함수들
 */
int IsEmpty(void){
    if(front==rear)//front와 rear가 같으면 큐는 비어있는 상태
        return true;
    else return false;
}

int IsFull(void){
    int tmp=(rear+1)%MAX; //원형 큐에서 rear+1을 MAX로 나눈 나머지값이
    if(tmp==front)//front와 같으면 큐는 가득차 있는 상태
        return true;
    else
        return false;
}

void addq(int value){
    if(IsFull())
        printf("Queue is Full.\n");
    else{
         rear = (rear+1)%MAX;
         queue[rear]=value;
        }

}
int deleteq(){
    if(IsEmpty()){
        printf("Queue is Empty.\n");
        return false;
    }
    else{
        front = (front+1)%MAX;
        return queue[front];
    }
}


/*
 Node로 이루어진 이진탐색 트리 초기화
 */

Node* BST_insert(Node* root, int profit, int weight, int bound)
{
    if(root == NULL)
    {
        root = (Node*)malloc(sizeof(Node));
        root->leftChild = root->rightChild = NULL;
        root->profit = profit;
        root->weight = weight;
        root->bound = bound;
        return root;
    }
    else
    {
        if(root->profit > profit)
            root->leftChild = BST_insert(root->leftChild, profit, weight, bound);
        else
            root->rightChild = BST_insert(root->rightChild, profit, weight, bound);
    }
    return root;
}


Node*   init_tree(Node* tree_root, int   profit, int weight, int bound)
{
    tree_root = BST_insert(tree_root, 0, 0, 60);
    
    return tree_root;
}


int main ()
{
    Node*   tree_root = (Node*)malloc(sizeof(Node));
    tree_root = init_tree(tree_root, 0, 0, 60);
    
    return 0;
}
