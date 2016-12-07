/*
    思路：
        ①：这又是一个比较坑的题目，主要问题在题目中描述的“只能在左右中选一个方向，在上下中选一个方向”。可以发现题目描述中的例子直观的解有 3 个（不可回退），但是
         由于有这一句的限制，导致给出的结果是 2
        ②：上面①的约束，也就是说如果某一步向左走就意味着永远不能向右走，如果某一个向下走了就意味着永远不能在往上走了。因为两个点总有一个相对方位，所以要想
            成功到达另一个点，其实要选的 “左右” “上下” 一开始就是确定的。这两个起始与终点构成了一个移动范围的矩形的两个顶点。
        ③：因为起点跟终点如果交换，路线是可逆的，解是一样的，所以可以通过调整，确定一个相对方向，这里设定 终点 在 起点的 右边（包含在一个列），如果不是交换起点
            与终点
        ④：从起点扫描可移动范围内所有点，一直扫描到终点。这种扫描方向根据上面的分析是确定的。
        ⑤：对于起点终点为对角的矩形，扫描的两条边界上所有可达的点到达路径数位 1 （因为只向一个方向，另一个轴不能移动，否则没法返回当前行或列），两条边界
            上所有不可达的点的到达路径书是 0
        ⑥：对于两条边界之外的任何一个点， 如果不可达，路径数 0 ，如果可达路径数 应该是 x 轴移动方向前一个点的路径数 + y轴移动方向前一个点的路径数

*/
#include <iostream>
#include <vector>

using namespace std;

class Visit {
public:
    int countPath(vector<vector<int> > map, int n, int m) {
        int x1, x2, y1, y2;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(map[i][j] == 1){
                    x1 = i;
                    y1 = j;
                }
                if(map[i][j] == 2){
                    x2 = i;
                    y2 = j;
                }
            }
        }
        //如果 x1 > x2，交换起始点与终点
        if(x1 > x2){
            int tempX = x1, tempY = y1;
            x1 = x2; y1 = y2;
            x2 = tempX, y2 = tempY;
        }


        vector<vector<int> > pathCouts(n,vector<int>(m, 0));
        pathCouts[x1][y1] = 1; //起点到自己有一个路径
        if(y1 <= y2){ //终点在右边
            //填充 x轴 边界
            for(int i = x1 + 1; i <= x2; i++){
                pathCouts[i][y1] = map[i][y1] == -1 ? 0 : pathCouts[i-1][y1];
            }
            //填充y轴边界
            for(int i = y1 + 1; i <= y2; i++){
                pathCouts[x1][i] = map[x1][i] == -1 ? 0 : pathCouts[x1][i-1];
            }
            //填充其他格子
            for(int i = x1 + 1; i <= x2; ++i){
                for(int j = y1 + 1; j <= y2; ++j){
                    pathCouts[i][j] = map[i][j] == -1 ? 0 : pathCouts[i-1][j] + pathCouts[i][j-1];
                }
            }
        }
        else { //终点在左边
            //填充 x轴 边界
            for(int i = x1 + 1; i <= x2; i++){
                pathCouts[i][y1] = map[i][y1] == -1 ? 0 : pathCouts[i-1][y1];
            }
            //填充y轴边界
            for(int i = y1 - 1; i >= y2; i--){
                pathCouts[x1][i] = map[x1][i] == -1 ? 0 : pathCouts[x1][i+1];
            }
            //填充其他格子
            for(int i = x1 + 1; i <= x2; ++i){
                for(int j = y1 - 1; j >= y2; --j){
                    pathCouts[i][j] = map[i][j] == -1 ? 0 : pathCouts[i-1][j] + pathCouts[i][j+1];
                }
            }
        }
        return pathCouts[x2][y2];
    }
};

int main(){
    vector<vector<int> > map;
    int arr1[] = {0,1,0}, arr2[] = {2, 0, 0};
    map.push_back(vector<int>(arr1, arr1 + 3));
    map.push_back(vector<int>(arr2, arr2 + 3));
    cout << (new Visit())->countPath(map, 2, 3) << endl;
    return 0;
}
