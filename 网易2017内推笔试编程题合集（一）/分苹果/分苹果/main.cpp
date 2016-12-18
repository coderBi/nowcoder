/*
    思路：
        贪婪策略：每次都将最大的数字减去 2 给最小的数字，然后重新排序。
        ----如果最大的与最小的数字相差 >= 2正常移动
        ----如果最大的数字与最小的数字相差 == 0 已经满足条件
        ----如果最大的与最小的差值 == 1 不可能时间均匀
*/
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_LENGTH 100

void swap(int arr[], int pos1, int pos2){
    int temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
}

int getMoveTimes(int arr[], int length){
    if(length <= 1)
        return 0;
    sort(arr, arr + length);

    int toReturn = 0;
    while(1){
        int sub = arr[length -1] - arr[0];
        bool flag = false; //是否跳出while循环
        switch(sub){
            case 0:
                flag = true;
                break;
            case 1:
                flag = true;
                toReturn = -1;
                break;
            default:
                arr[length - 1] -= 2;
                arr[0] += 2;
                //重新插入到元素组
                for(int i = 0; i < length - 2 && arr[i] > arr[i + 1]; ++i) //前n-1位排序
                    swap(arr, i, i+1);
                for(int i = length -1; i > 0 && arr[i] < arr[i -1]; --i) //插入第n位
                    swap(arr,i,i-1);
                toReturn++;
                break;
        }
        if(flag)
            break;
    }
    return toReturn;
}

int main()
{
    int n, arr[MAX_LENGTH] = {0};
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }
    cout << getMoveTimes(arr,n) << endl;
    return 0;
}
