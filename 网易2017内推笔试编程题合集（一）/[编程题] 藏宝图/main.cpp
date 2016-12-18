#include <iostream>

using namespace std;

int main()
{
    string s, t;
    while(cin >> s >> t){
        string result = "Yes";
        int i = 0;
        for(int j = 0; j < t.size(); ++j){
            while(i < s.size() && s.at(i) != t.at(j)){++i;}
            if(i >= s.size()){
                result = "No";
                break;
            }
            i++; //从下一位开始查找下一个字符
        }
        cout << result << endl;
    }
    return 0;
}
