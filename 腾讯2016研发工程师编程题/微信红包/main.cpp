#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Gift {
public:
    int getValue(vector<int> gifts, int n){
        map<int, int> valueMap;
        int i;

        for(i = 0; i < n; i++){
            if(valueMap.end() == valueMap.find(gifts[i])){
                valueMap[gifts[i]] = 1;
            } else {
                valueMap[gifts[i]]++;
            }
        }

        map<int, int> ::iterator it, iend = valueMap.end();
        for(it = valueMap.begin(); it != iend; it++){
            if(it->second > (n / 2)){
                return it->first;
                break;
            }
        }
        return 0;
    }
};

int main()
{
    int n, i;
    cin >> n;

    int * arr = new int[n];
    for(i = 0; i < n; i++){
        cin >> arr[i];
    }
    vector<int> v(arr, arr + n);
    cout << (new Gift())->getValue(v, n) << endl;
    return 0;
}
