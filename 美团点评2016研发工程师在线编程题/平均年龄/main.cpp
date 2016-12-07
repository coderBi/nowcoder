/*
    思路：
        这题目略坑，第一点，题目说是从今年3月末开始计算，但是又是每年3月末进行平均年龄的更新，所以存在给出的数据是今年重新计算过的还是没计算的不清楚。
        第二点，题目没有说明要进行多组数据输入，但是提交的时候发现要处理多组数据。

*/
#include <iostream>

using namespace std;

#define AGE_OF_NEW_EMPLOYEE 21

int main()
{
    double W, Y, N;
    double x;
    while(cin >> W >> Y >> x >> N){

        double toLeft = 0; //今年离职人数
        for(double i = 1; i <= N; ++i){
            toLeft += W * x;
            if(toLeft < 1){ //如果离职人数小于 1 ，说明没有人离职，Y++
                Y++;
                continue;
            }
            int iToleft = (int)toLeft; //去整数，为离职人数
            toLeft -= iToleft;
            Y = (iToleft * AGE_OF_NEW_EMPLOYEE + (W - iToleft) * (Y+1)) / W;
        }

        //向上取整
        if(Y > (int)Y)
            Y = (int)Y + 1;
        else
            Y = (int)Y;
        cout << Y << endl;
    }
    return 0;
}
