#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

class GrayCode {
public:
    vector<string> getGray(int n) {
        vector<string>  toReturn;
        if(n == 1){
            toReturn.push_back("0");
            toReturn.push_back("1");
            return toReturn;
        }
        vector<string> child = getGray(n - 1);
        unsigned int i;
        for(i = 0; i < child.size(); i++){
            if(i % 2 == 0){
                toReturn.push_back(child[i] + "0");
                toReturn.push_back(child[i] + "1");
            } else {
                toReturn.push_back(child[i] + "1");
                toReturn.push_back(child[i] + "0");
            }
        }
        return toReturn;
    }
};

int main()
{
    int n;
    while(-1 != scanf("%d", &n)){
        vector<string> result = (new GrayCode())->getGray(n);
        unsigned int i;
        for(i = 0; i < result.size(); i++){
            cout << result[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
