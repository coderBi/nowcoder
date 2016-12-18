/*
    思路：
        ①： 一开始求出平均值
        ②：排序后，大数字一直给小数字，任意一个数如果发现与平均数相差不是 2 的倍数就失败。
*/
#include <iostream>

using namespace std;

#define MAX_LENGTH 100

int getAvg(int arr[], int length){
    int sum = 0;
    for(int i = 0; i < length; ++i)
        sum += arr[i];
    if(sum%length != 0) //平均是是小数，没法平分
        return -1;
    return sum/length;
}

int getMoveTimes(int arr[], int length){
    int avg = getAvg(arr, length);
    int toReturn = 0;
    if(avg < 0)
        return -1;
    for(int i = 0; i < length; ++i){
        int sub = arr[i] - avg;
        if(sub%2 != 0) //与平均数相差不是2的整数倍，没有办法通过给予形成平均
            return -1;
        if(arr[i] > avg){
            toReturn += sub/2;  //不管是给谁了，反正是给了
        }
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
