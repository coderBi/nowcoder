/*
    思路：
        ①： 先找出不包含看不清的现有序列中顺序对的数量
        ②：题目描述看不清的最多有 10处，因为是 1 ~ n的数字数列，通过排序后可以将看不清的数字子序列找出来。
        ③：数字子序列排序 A(10,10) 进行逐一分析，目测复杂度可能会有问题。
        ④：先求出所有的排列情况, k！。之前认为可以对这个集合带入进行 “二分法”求解，但是通过仔细分析，发现二分法是不可行的。例如 4123 这样的序列带入的
         所得的顺序对可能比 3421 这样的要更多一些，而 前面的 4123 在所有的集合里面更靠后，按说是 更倾向于 "倒叙"。这样就否定了二分法的可行性。
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > getSubLists(vector<int> list){ //生成所有的排列
	vector<vector<int> > toReturn;
	if(list.size() == 0){
		return toReturn;
	}
	if(list.size() <= 1){
		toReturn.push_back(list);
		return toReturn;
	}

	bool moveNext = false;
	do{
		moveNext = false;
		vector<vector<int> > subV = getSubLists(vector<int>(list.begin()+1, list.end()));
		for(unsigned int i = 0; i < subV.size(); ++i){
			subV[i].insert(subV[i].begin(),list[0]);
			toReturn.push_back(subV[i]);
		}

		int exPos = -1;
		for(unsigned int i = 1; i < list.size(); ++i){ // 找到最小的比第一位大的后续元素  //过程其实就是交换 list[0] list[1], 交换 list[0] list[2] ....
			if(list[i] > list[0]){
				moveNext = true;
				if(exPos == -1 || list[exPos] > list[i])
					exPos = i;
			}
		}

        if(exPos != -1){
            int temp = list[0]; list[0] = list[exPos]; list[exPos] = temp;
        }
		sort(list.begin() + 1, list.end()); //实际发现这一行代码有时候可以省略,前提是初始提供的序列已经排好为最小序列，例如 1234。如果给定初始是 2314这样的还是要排序

	}while(moveNext);

	return toReturn;
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n + 1, 0); // v[0] 不用
    vector<int> vMap(n + 1, 0); //用于比对提取看不到的数字集合
    vector<int> restNum, restScript;

    //录入
    for(int i =1; i <= n; ++i){
        cin >> v[i];
        vMap[v[i]] = 1;
    }

     //提取看不见的数字脚标
    for(int i = 1; i <= n; ++i){
        if(v[i] == 0)
            restScript.push_back(i);
    }

    //提取看不见的数字
    for(int i = 1; i <= n; ++i){
        if(vMap[i] == 0)
            restNum.push_back(i);
    }
    sort(restNum.begin(), restNum.end()); //这里可以省去，因为，本身就是从小数字到大数字扫描的

    vector <vector<int> > lists = getSubLists(restNum);

    int preK = 0; //没有看不到的那些数字的集合可以形成的顺序对个数
    for(unsigned int i = 1; i < v.size(); ++i){
        if(v[i] != 0){
            for(unsigned int j = i + 1; j < v.size(); ++j){
                if(v[j] != 0 && v[i] < v[j])
                    preK++;
            }
        }
    }

    int restK = k - preK; //添加了看不到的集合后需要刚好多出来的 顺序对数
    int res = 0;
    for(unsigned int s = 0; s < lists.size(); ++s){
        vector<int> vIn = lists[s];
        int desK = 0; // 保存实际计算多出来的顺序对
        for(unsigned int i = 1; i < v.size(); ++i){
            for(unsigned int j = i + 1; j < v.size(); ++j){
                if(v[i] != 0 && v[j] != 0) //计算过了
                    continue;
                int a = v[i] == 0 ? vIn[find(restScript.begin(), restScript.end(), i) - restScript.begin()] : v[i];
                int b = v[j] == 0 ? vIn[find(restScript.begin(), restScript.end(), j) - restScript.begin()] : v[j];
                a < b ? desK++ : 0;
            }
        }
        if(desK == restK)
           res++;
    }
    cout << res << endl;
    return 0;
}
