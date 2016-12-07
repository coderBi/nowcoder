#include <iostream>
#include <vector>

using namespace std;

class LongestDistance {
public:
    int getDis(vector<int> A, int n) {
        int toReturn = 0;
        for(int i = 0; i < n; ++i){
            int a = A[i], b = A[i]; //减数 被减数
            for(int j = i + 1; j < n; j++){
                if(A[j] > b)
                    b = A[j];
            }
            toReturn = toReturn < (b - a) ? (b - a) : toReturn;
        }
        return toReturn;
    }
};

int main()
{
    int arr[] = {10, 5};
    cout << (new LongestDistance())->getDis(vector<int>(arr,arr+2), 2) << endl;
    return 0;
}
