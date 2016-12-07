#include <iostream>
#include <vector>

using namespace std;

class Stock {
public:
    int maxProfix(vector<int> prices, int n){
        vector<int> maxArr; //存储每一个买入点之后可以获得的最大收益
        vector<vector<int> > allProfix; //存储每一个买入点可能的所有收益结果
        int toReturn = 0;

        unsigned int size = prices.size();
        for(unsigned int i = 0; i < size; ++i){ //初始化最大收益数组，初始值为0
            maxArr.insert(maxArr.begin() + i, 0);
        }
        for(unsigned int i = 0; i < size; ++i){ //填充所有收益数组
            vector<int> itemProfix;
            for(unsigned int j = 0; j < i; ++j){ //前面填充为0，这里出现了冗余空间没有使用，有待处理优化。
                itemProfix.insert(itemProfix.begin()+j, 0);
            }
            for(unsigned int j = i; j < size; ++j){
                itemProfix.insert(itemProfix.begin()+j, prices[j] - prices[i]);
                if(itemProfix[j] > maxArr[i])
                    maxArr[i] = itemProfix[j];
            }
            allProfix.insert(allProfix.begin() + i, itemProfix);
        }

        //获取最大收益
        for(unsigned int i = 0; i < size; ++i){
            int profix;
            for(unsigned int j = i; j < size; ++j){
                profix = allProfix[i][j];

                int secondProfix = maxArr[j];
                for(int k = j + 1; k < size; ++k){
                    if(secondProfix < maxArr[k])
                        secondProfix = maxArr[k];
                }
                profix +=  secondProfix;

                if(profix > toReturn)
                    toReturn = profix;
            }
        }
        return toReturn;
    }
};

int main()
{
    vector<int> v;
    /*v.push_back(10);
    v.push_back(22);
    v.push_back(5);
    v.push_back(75);
    v.push_back(65);
    v.push_back(80);*/

    v.push_back(235);
    v.push_back(55);
    v.push_back(628);
    v.push_back(455);
    v.push_back(414);
    v.push_back(547);
    v.push_back(454);
    cout << (new Stock())->maxProfix(v,v.size()) << endl;
    return 0;
}
