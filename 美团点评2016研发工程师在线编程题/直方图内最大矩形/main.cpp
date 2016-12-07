#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class MaxInnerRec {
public:
    int countArea(vector<int> A, int n) {
        int toReturn = 0;
        for(int i = 0; i < n; i++){
            int left = 0, right = 0;
            int sq; //面积

            for(left = i; left >= 0 && A[left] >= A[i]; left--){}
            for(right = i; right < n && A[right] >= A[i]; right++){}
            sq = A[i] * (right - left + 1 -2); //减2 是因为righ 跟 left都是不符合的元素.
            toReturn = sq > toReturn ? sq : toReturn;
        }
        return toReturn;
    }
};

int main()
{
    printf("Hello world!\n");
    return 0;
}
