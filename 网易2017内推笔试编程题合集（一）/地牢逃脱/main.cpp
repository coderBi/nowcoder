/*
    思路：
        ①：用广度优先搜索，只是常规的广度每次是向下移动一个距离，这个存在给出k种移动方式。
        ②：这题表述真他妈坑，一开始提交有一个用例没通过，后来发现很多人都死在这个用例上，通过研究发现是题目的意思是如果地图上出现了“.” 不可达，就输出-1
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct _Step{
    int x;
    int y;
} Step, PStep;

int main()
{
    int n, m, k;
    cin >> n >> m;
    vector<vector<char> > v(n,vector<char>(m,'\0'));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            cin >> v[i][j];
    }
    Step pos;
    cin >> pos.x >> pos.y;
    cin >> k;
    vector<Step> steps(k,Step());
    for(int i = 0; i < k; ++i)
        cin >> steps[i].x >> steps[i].y;
    queue<Step> positons;
    positons.push(pos);
    v[pos.x][pos.y] = 'X'; //起始点设置为不可达


    int result = 0;
    while(positons.size() > 0){
        queue<Step> nextPositions; //下一层节点集合
        bool canReach = false;
        while(positons.size() > 0){ //内循环会清空原有的集合，生成下一层节点集合
            Step node = positons.front();
            positons.pop();
            Step nextPos;

            for(int i = 0; i < k; ++i){
                nextPos.x = node.x + steps[i].x;
                nextPos.y = node.y + steps[i].y;
                if(nextPos.x >= 0 && nextPos.x < n
                   && nextPos.y >= 0 && nextPos.y < m
                   && v[nextPos.x][nextPos.y] != 'X'){
                    v[nextPos.x][nextPos.y] = 'X'; //如果下一个节点是可达的，就设置位不可达，并且在后面让深度加一
                    nextPositions.push(nextPos);
                    canReach = true;
                }
            }
        }
        if(canReach){ //可达
            result++;
        }
        positons = nextPositions;  //下一层的节点集合
    }
    //这题坑爹的地方在这里，最后判断如果有"."，不可达，就返回-1
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(v[i][j] == '.'){
                result = -1;
                break;
            }
        }
        if(result == -1)
            break;
    }
    cout << result;
    return 0;
}
