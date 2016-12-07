/*
    改进超时思路：之前分析的超时原因是每次添加一个元素，都得先遍历链表找到尾巴再移动到头部。这个遍历过程很耗时。解决的思路是使用双线链表
*/
#include <iostream>

using namespace std;


typedef struct _Node {
    int num;
    struct _Node * next;
    struct _Node * previous;
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
    Node * head = NULL, *tail = NULL;
    for(int i = n; i > 0; i--){
        //将n添加到队队front
        Node * node = new Node();
        node->num = i;
        node->next = head;
        node->previous = NULL;
        if(head != NULL){
            head->previous = node;
        }
        head = node;

        //将队列最后一个移动到队首
        if(tail == NULL){ //队尾是空
            tail = head;
        } else { //尾巴不是头，进行移动
            tail->next = head;
            head->previous = tail;

            //重置尾巴与头
            Node * nextTail = tail->previous;
            nextTail->next = NULL; //tail不为空运行到这里最起码有2个元素，所以不用进行tail->previous是否为空的判读。
            tail->previous = NULL;
            head = tail;
            tail = nextTail;
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
