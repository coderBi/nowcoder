#include <iostream>

using namespace std;

#define MAX_LENGTH 200

void printArr(int arr[], int length){
    for(int i = 0; i < length - 1; ++i){
        cout << arr[i] << " ";
    }
    cout << arr[length -1] << endl;
}

void sortCards(int input[], int result[], int n){ //n表示的是一半的数组长度
    for(int i = 0, j = 0; i < n; ++i){
        result[j++] = input[i];
        result[j++] = input[i + n];
    }

    //拷贝回去原数组
    for(int i = 0; i < 2 * n; ++i){
        input[i] = result[i];
    }
}

int main()
{
    int t, n, k;
    int input[MAX_LENGTH] = {0}, result[MAX_LENGTH] = {0};

    cin >> t;
    for(int i = 0; i < t; ++i){
        //数据输入
        cin >> n >> k;
        for(int j = 0; j < 2*n; ++j){
            cin >> input[j];
        }

        //洗牌
        for(int j = 0; j < k; ++j)
            sortCards(input, result, n);

        //打印输出
        printArr(input, 2* n);
    }
    return 0;
}
