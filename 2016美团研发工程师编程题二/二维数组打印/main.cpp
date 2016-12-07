#include <iostream>
#include <vector>

using namespace std;

class Printer {
public:
    vector<int> arrayPrint(vector<vector<int> > arr, int n) {
        vector<int> toReturn;
        if( n != arr.size())
            n = arr.size();

        //打印对角线右上部分
        for(int j = n - 1; j >= 0; j--){
            for(int i = 0, k = j; i < n && k < n; i++, k++){
                toReturn.push_back(arr[i][k]);
            }
        }

        //打印对角线左下部分
        for(int i = 1; i < n; i++){
            for(int j = 0, k = i; j < n && k < n; j++, k++){
                toReturn.push_back(arr[k][j]);
            }
        }
        return toReturn;
    }
};

int main()
{
    vector<vector<int> > arr;
    for(int i = 0; i <= 3; i++){
        vector<int> subArr;
        for(int j = 1; j <= 4; j++){
            subArr.push_back(i*4 + j);
        }
        arr.push_back(subArr);
    }
    vector<int> result = (new Printer())->arrayPrint(arr,4);
    for(int i = 0; i < result.size(); i++){
        cout << result[i] << "  ";
    }
    return 0;
}
