#include <iostream>
#include <vector>

using namespace std;

int getTheLast(const vector<int> & v){
    unsigned int size = v.size();
    switch(size){
        case 0:
           return -1; //没有提供任何数据， 返回-1
        case 1:
            return v[0];  //只有一位，就返回这个数
        default:
            vector<int> sub;
            for(unsigned int i = 1; i < size; i += 2){
                sub.push_back(v[i]);
            }
            return getTheLast(sub);
    }
}

int main()
{
    int n;
    while(cin.peek() != cin.eof()){
        vector<int> v;
        cin >> n;
        for(int i = 0; i <= n; i++){
            v.push_back(i);
        }

        cout << getTheLast(v) << endl;
        cin.sync(); //清空输入缓存，避免下次输入收到干扰
    }
    return 0;
}
