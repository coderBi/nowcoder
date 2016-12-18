/*
    思路：
        ①：初步分析，如果每次有 d 个选择，那么复杂度大概  d ^ k 题目中给的 d <= 50 k <= 10，暴力的复杂度不能满足要求。
        ②： 利用动态规划，如果 maxMulti[i][j] 表示在前 i 个人中 找j个人（并且索引为i的是最后选择的一个元素）的最大乘积，那么分析最后一个找到的人
            如果他的值是负数，那么前面要找的是 j -1个的乘积的最小值，如果他是整数，那么要找的前面j-1个的乘积的最大值。
        ③：通过②的描述，中间结果需要存储最大跟最小的结果。
        ④：最终在所有找了相应人数中的结果中查找最大值。
        ⑤：题目中最大乘积可能是 50 * 10，所以数据应该用long long
*/
#include <iostream>
#include <vector>

using namespace std;

#define MAX_LENGTH 50



long long getMaxMulti(int arr[], int length, int k, int d){
    vector<vector<long long> > maxArr(length,vector<long long>(k+1)), minArr(length,vector<long long>(k+1));
    for(int i = 0; i < length; ++i){
        maxArr[i][1] = minArr[i][1] = arr[i]; //只选择一个元素
    }
    for(int j = 2; j <= k; ++j){
        long long multiMax, multiMin;
        for(int i = j -1; i < length; ++i){
            int bottom = i - d >= 0 ? i - d : 0;
            for(int m = i - 1; m >= bottom; --m){
                multiMax = maxArr[m][j-1] * arr[i];
                multiMin = minArr[m][j-1] * arr[i];
                if(multiMax < multiMin){
                    long long temp = multiMax;
                    multiMax = multiMin;
                    multiMin = temp;
                }
                if(m == i - 1){
                    maxArr[i][j] = multiMax;
                    minArr[i][j] = multiMin;
                } else {
                    if(maxArr[i][j] < multiMax)
                        maxArr[i][j] =  multiMax;
                    if(minArr[i][j] > multiMin)
                        minArr[i][j] = multiMin;
                }
            }
        }
    }

    //查找maxArr[i][k],获取最大值
    long long toReturn = maxArr[k-1][k];
    for(int i = k; i < length; ++i){
        if(toReturn < maxArr[i][k])
            toReturn = maxArr[i][k];
    }
    return toReturn;
}

int main()
{
    int n, arr[MAX_LENGTH] = {0};
    int k, d;
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }
    cin >> k >> d;
    cout << getMaxMulti(arr, n, k ,d) << endl;
    return 0;
}
