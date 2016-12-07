#include <iostream>

using namespace std;


typedef struct _Node {
    int num;
    struct _Node * next;
} Node;

void printArr(Node * head){
    if(head == NULL){
        cout << endl;
        return;
    }

    Node * node = head;
    for(; node != NULL && node->next != NULL; node = node->next){
        cout << node->num << " ";
    }
    cout << node->num << endl;
}

void freeList(Node * head){
    for(Node * node = head, *nextNode = NULL; node != NULL; node = nextNode){
        nextNode = node->next;
        delete node;
    }
}

Node * getArray(int n){
    Node * head = NULL;
    for(int i = n; i > 0; i--){
        //将n添加到队队front
        Node * node = new Node();
        node->num = i;
        node->next = head;
        head = node;

        //将队列最后一个移动到队首
        Node * pre = NULL, *tail = NULL;
        for(tail = head; tail != NULL && tail->next != NULL; pre = tail, tail = tail->next){} //这里的遍历应该是超时的原因，整个程序这里的复杂度 n * n
        if(tail != head){ //尾巴不是头，进行移动
            tail->next = head;
            head = tail;
            pre->next = NULL;
        }
    }
    return head;
}

int main()
{
    int t, n;

    cin >> t;
    for(int i = 0; i < t; ++i){
        cin >> n;
        Node * result = getArray(n);
        printArr(result);
        freeList(result);
    }
    return 0;
}
