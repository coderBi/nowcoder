#include <iostream>
#include <vector>

using namespace std;

class Flip {
public:
    vector<vector<int> > flipChess(vector<vector<int> > A, vector<vector<int> > f) {
        for(unsigned int i = 0; i < f.size(); i++){
            int x = f[i][0] - 1;
            int y = f[i][1] - 1;

            (x -1) >= 0 ? (A[x-1][y] = (A[x-1][y] == 0 ? 1 : 0)) : 0; //上面
            (x +1) < A.size() ? (A[x+1][y] = (A[x+1][y] == 0 ? 1 : 0)) : 0; //下面
            (y -1) >= 0 ? (A[x][y-1] = (A[x][y-1] == 0 ? 1 : 0)) : 0;  //左边
            (y +1) < A[x].size() ? (A[x][y+1] = (A[x][y+1] == 0 ? 1 : 0)) : 0; //右边
        }
        return A;
    }
};

int main()
{
    return 0;
}
