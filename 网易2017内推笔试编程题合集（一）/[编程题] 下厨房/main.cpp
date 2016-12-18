#include <iostream>
#include <set>

using namespace std;

int main()
{
    set<string> detail;
    string input;
    while(cin >> input){
        set<string>::iterator it;
        if((it = detail.find(input)) == detail.end())
            detail.insert(it,input);
    }
    cout << detail.size();
    return 0;
}
