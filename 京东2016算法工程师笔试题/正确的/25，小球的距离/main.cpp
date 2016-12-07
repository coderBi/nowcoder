#include <iostream>

using namespace std;

class Balls {
public:
    int calcDistance(int A, int B, int C, int D){
        int result = 0;
        float temp, fResult = 0;
        for(temp = A; temp > 0; temp /= 2){fResult += temp + temp/2;}
        for(temp = B; temp > 0; temp /= 2){fResult += temp + temp/2;}
        for(temp = C; temp > 0; temp /= 2){fResult += temp + temp/2;}
        for(temp = D; temp > 0; temp /= 2){fResult += temp + temp/2;}
        result = fResult + 0.5; //四舍五入
        return result;
    }
};

int main()
{
    int a,b,c,d;
    Balls balls;
    while(cin >> a >> b >> c >> d){
        cout << balls.calcDistance(a,b,c,d) << endl;
    }
    return 0;
}
