/*
    思路1：
        ①：利用递推思想，如果本身就是切成 n * m, 那么现在只需要取出来最小的格子就行了。
        ②：上面的这个最小的格子，如果在最终的分配中没有跟 上下或者左右进行合并，那么，最终的最小结果就是它。 如果进行了合并，那么新的问题就是将当前
            已经合并的矩阵 分割成 4 * 4 求最大的“最小值”，问题规模得到了缩小
        ③：重复分析① ②， 最终可以合并出来  4 * 4
        ④：上述的方案很明显 复杂度是 4 的幂， 这是一种糟糕的算法。类似于递归斐波那契数列。
    思路2：
        ①： 横切组合数 C(n,3) 竖切组合数 C(m, 3)。 二者相乘的上限是 C(75,3) * C(75, 3)， 这是一个很大的数据。
        ②：在横切之后， 分析竖切，由于横向的切法已经固定了， 那么竖切在此基础上可以受到约束而减少判断次数.
        ③：在上面②的基础上分析， 如果竖切 第一刀定了， 那么第二刀就可以在这个基础上缩小范围。这里利用二分法，假定，最大获利是 mid，然后保证每一刀都
            可以切出保证最大获利 >= mid
        ④：接着③ 分析第一刀，如果，从左到右移动第一刀，刚好满足第一刀切出来的四个格子都 >= mid 那么第一刀就这么定了。因为，要保证后面尽可能满足切法，
            所以第一刀最好的位置就是这个 “刚好”满足的点。 同样可以分析第二刀 第三刀
        ⑤：最终满足切法，按上满的切法，可能存在边缘多出来一部分，而这一多出来的部分又没有办法满足加大 mid的 切法。 所以如果切成 4 * 4 这一多出来的部分只能
            被动合并。
        ⑥： 这种思路的复杂度： 切三刀 C(n, 3) (可以先找到n m 中间的较小者，在那个方向上先切三刀。这里的n 最合理的取值是 min(n,m)) *  另一个方向扫描 m (实际
                为 n m 中的较大者) * 二分查找的次数 ln((所有数的和 / 16))( 题目说每一个数字是 0 ~ 9 ， 那么所以数字和大概上限 75 * 75 * 9)
*/
#include <iostream>
#include <stdio.h>
#include <vector>

//这里定义横向与竖向刀数，方便程序扩展
#define DAO_NUM_X 3
#define DAO_NUM_Y 3
//定义最大的 n m
#define MAX_N 75
#define MAX_M 75

using namespace std;

int sum[MAX_N][MAX_M]; //全局变量，自动初始化 0  // 定义每一个节点到左上角区域构成的矩形的所有的数字的和

void getAllSums(vector<vector<int> > v, int n, int m){
    //左顶点
    sum[0][0] = v[0][0];
    //上边
    for(int i = 1; i < m; ++i){
        sum[0][i] = v[0][i] + sum[0][i-1]; //当前加上左边的所有和
    }
    //左边
    for(int i = 1; i < n; ++i){
        sum[i][0] = v[i][0] + sum[i-1][0]; //当前加上上面的所有和
    }
    //中间
    for(int i = 1; i < n; ++i){
        for(int j = 1; j < m; ++j){
            sum[i][j] = v[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        }
    }
}

/**
    * x2 y2是矩形的 右下角坐标， x1 y1 是左上角坐标
*/
int getAreaSum(int x1, int y1, int x2, int y2){ //得到一个区域的数字和
    bool topIsZero = x1 == 0 ? true : false , leftIsZero =  y1 == 0 ? true : false; //这个矩形是否 上面没有元素， 是否左边没有元素
    int toReturn =  sum[x2][y2] - (topIsZero ? 0 : sum[x1-1][y2])
                    - (leftIsZero ? 0 : sum[x2][y1-1]) + ( (!topIsZero && !leftIsZero) ?  sum[x1-1][y1-1] : 0);
    return toReturn;
}

int getMaxProfit(vector<vector<int> > v, int n, int m){
    getAllSums(v, n, m);
    int result = 0;

    if(n < m){ //先竖切
        for(int i = 0; i < m - 3; ++i)
            for(int j = i + 1; j < m - 2; ++j)
                for(int s = j + 1; s < m - 1; ++s){
                    for(int left = 0, right = sum[n-1][m-1] / 16; left <= right; ){
                        int cuts = 0; //横向切的块数（不包括最下面没被切的多余部分）
                        int mid = (left + right) / 2;
                        for(int bottom = 0, top = 0; bottom < n; ++bottom){
                            int area1 = getAreaSum(top, 0, bottom, i);
                            int area2 = getAreaSum(top, i+1, bottom, j);
                            int area3 = getAreaSum(top, j+1, bottom, s);
                            int area4 = getAreaSum(top, s+1, bottom, m-1);
                            if(area1 <= mid && area2 <= mid
                               && area3 <= mid && area4 <= mid){
                                    cuts++;
                                    if(cuts == 4){
                                        break;
                                    }
                                    top = bottom + 1;
                               }
                        }
                        if(cuts == 4){ //可以切4块，说明mid可能偏小
                            result = result < mid ? mid : result; //result是所有可能结果中最大的
                            left = mid+1;
                        } else { //没有切到 4 块，说明 mid 太大了
                            right = mid -1;
                        }
                    }
                }

    } else { //先横切
        for(int i = 0; i < n- 3; ++i)
            for(int j = i + 1; j <n - 2; ++j)
                for(int s = j + 1; s < n - 1; ++s){
                    for(int left = 0, right = sum[n-1][m-1] / 16; left <= right; ){
                        int cuts = 0; //横向切的块数（不包括最下面没被切的多余部分）
                        int mid = (left + right) / 2;
                        for(int rc = 0, lc = 0; rc < m; ++rc){
                            int area1 = getAreaSum(0, lc, i, rc);
                            int area2 = getAreaSum(i+1, lc, j, rc);
                            int area3 = getAreaSum(j+1, lc, s, rc);
                            int area4 = getAreaSum(s+1, lc, n-1, rc);
                            if(area1 >= mid && area2 >= mid
                               && area3 >= mid && area4 >= mid){
                                    cuts++;
                                    if(cuts == 4){
                                        break;
                                    }
                                    lc = rc + 1;
                               }
                        }
                        if(cuts == 4){ //可以切4块，说明mid可能偏小
                            result = result < mid ? mid : result;
                            left = mid+1;
                        } else { //没有切到 4 块，说明 mid 太大了
                            right = mid -1;
                        }
                    }
                }
    }
    return result;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int> > v(n, vector<int>(m,0));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j){
            scanf("%1d", &v[i][j]);
        }

    cout << getMaxProfit(v,n,m) << endl;
    return 0;
}
