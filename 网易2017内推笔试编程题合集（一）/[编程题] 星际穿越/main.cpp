/*
    思路：
        题目要求一个最大的整数，满足 x + x*x <= h
*/
#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    unsigned long long h;
    while(cin >> h){
        unsigned long long result = floor(sqrt(h));
        while(result > 0){
            if((result + result * result) <= h)  //这里之前存在一个bug: result + result * result 由于result类型是 unsigned int 导致这个结果也是unsigned int
                break;
            result--;
        }
        cout << result << endl;
    }
    return 0;
}
