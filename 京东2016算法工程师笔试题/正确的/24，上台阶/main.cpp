#include <iostream>

using namespace std;

class GoUpstairs {
public:
    int countWays(int n){
        int maxStep = 2; //最大步长2
        #define MOD 1000000007
        int *steps = new int[n];
        steps[0] = 0;
        for(int i = 1; i < n; ++i){
            int bottom = (i - maxStep) >= 0 ? (i - maxStep) : 0;
            steps[i] = 0;
            for(int j = i - 1; j >= bottom; --j){
                steps[i] = steps[j] != 0 ? (steps[i] + steps[j]) % MOD : (steps[i] + 1) % MOD;
            }

        }
        int toReturn = steps[n-1];
        delete[] steps;
        return toReturn;
    }
};

int main()
{
    int n;
    GoUpstairs gu;
    while(cin >> n){
        cout << gu.countWays(n) << endl;
    }
    return 0;
}
