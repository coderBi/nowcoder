#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    while(cin.peek() != cin.eof()){
        vector<int> v;
        cin >> n;
        for(int i = 0; i <= n; i++){
            v.push_back(i);
        }
        while(v.size() > 1){
            //因为如果从前面往后面删除，会导致后面的索引改变，所以这里我采用从数组的大脚标开始操作
            int maxPrime = v.size();
            if(maxPrime % 2 == 0)
                maxPrime--;
            for(int i = maxPrime; i >= 1; i -= 2){
                v.erase(v.begin() + i -1);
            }
        }
        cout << v[0] << endl;
        cin.sync(); //清空输入缓存，避免下次输入收到干扰
    }
    return 0;
}
