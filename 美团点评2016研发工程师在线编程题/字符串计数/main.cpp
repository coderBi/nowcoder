/*
    思路；
        ①： 26进制相减，其中 a 字符相当于 0.
        ②： 对于某一个长度，如果两个字符串长度不够，就在后面追加 a
        ③：如果s1 后面有追加的 a，则说明 对于这个长度的 s1最小的“数”应该符合条件，也就是在原始给出的两个串之间
        ④：如果s2 后面有追加（或者s2长度刚好没追加跟给定长度一样），择说明s2 中对应长度的字符串不符合条件。
        ⑤：如果直接用填充a 之后的 s2 与 s1进行 26进制相减，那么可以理解为对于一个长度 s2中对应子串是要的，而s1 中是不要的，这个类似于10进制相减，去头不去尾
            。在相减基础之上针对 ③ ④ 的判断进行调整一个长度的结果
        ⑥：如果某一个长度的 s2 与 s1 子串完全相同，而且s2 符合了条件 ④，会导致返回的结果是 -1，根据现实情况，这里调整为 0

*/
#include <iostream>
#include <stdio.h>

#define MOD_NUMBER 1000007
#define MAX_LENGTH 100000

using namespace std;

int getMod(int number){
    return (number % MOD_NUMBER);
}

int getCountOneLength(string s1, string s2, int len, int s1Len, int s2Len){
    int *sub = new int[len];
    int toReturn = 0;
    for(int i = 0; i < len; i++){
        sub[i] = s2[i] - s1[i];
        toReturn = getMod(toReturn * 26 + sub[i]);
    }
    if(s1Len < len)
        toReturn++;
    if(s2Len <= len)
        toReturn--;
    delete[] sub;
    return getMod(toReturn);
}

int main()
{
    string s1, s2;
    int len1, len2;
    while(cin >> s1 >> s2 >> len1 >> len2){  //cin默认以空格分割，所以这里可以直接输入
        int s1Len = s1.length(), s2Len = s2.length(), result = 0;
        string s1Add = s1, s2Add = s2;
        for(int i = s1Len; i < len2; ++i)
            s1Add += "a";
        for(int i = s2Len; i < len2; ++i)
            s2Add += "a";

        for(int i = len1; i <= len2; ++i){
            int countOneLength = getCountOneLength(s1Add, s2Add, i, s1Len, s2Len);
            //上面的算法，如果出现s1 s2 相同，就会返回 -1； 根据现实情况，这里让结果为 0
            if(countOneLength < 0)
                countOneLength = 0;
            result = getMod(result + countOneLength);
        }

        cout << result << endl;
    }

    return 0;
}
