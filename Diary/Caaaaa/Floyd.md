### 全局最短路

一篇解释很好的文章：https://www.cnblogs.com/wangyuliang/p/9216365.html
1. 全局最短路
用一句话概括就是：从 i 号顶点到 j 号顶点只经过前 k 号点的最短路程。
核心代码：
```
    for(k=1;k<=n;k++)  
    for(i=1;i<=n;i++)  
    for(j=1;j<=n;j++)  
    if(e[i][j]>e[i][k]+e[k][j])  
          e[i][j]=e[i][k]+e[k][j];
```
2. 最小环问题
都比较容易得到从 u 到 v 经过中间某一些结点的最短路，但是我们得确保回来的时候，不能经过那些结点，这样我们就需要改一下 floyd 算法了。
核心代码：
```
int mincircle = infinity;
Dist = Graph;

for(int k=0;k<nVertex;++k){
    //新增部分:
    for(int i=0;i<k;++i)
        for(int j=0;j<i;++j)
            mincircle = min(mincircle,Dist[i][j]+Graph[j][k]+Graph[k][i]);
    //通常的 floyd 部分:
    for(int i=0;i<nVertex;++i)
        for(int j=0;j<i;++j){
            int temp = Dist[i][k] + Disk[k][j];
            if(temp < Dist[i][j])
                Dist[i][j] = Dist[j][i] = temp;
        }
}
 ```
 
- Floyd 算法保证了最外层循环到 k 时所有顶点间已求得以 0…k-1 为中间点的最短路径。
- 新增部分在前面：因为在之前的最短路径更新过程中, k 没有参与更新,所以dist[i][j]所表示的路径中不会有点 k ,即一定为一个环;

一个环至少有3个顶点，设某环编号最大的顶点为 L ，在环中直接与之相连的两个顶点编号分别为 M 和 N (M,N < L)，则最大编号为 L 的最小环长度:
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;*Graph(M,L) + Graph(N,L) + Dist(M,N)* 
&emsp;&emsp;其中 Dist(M,N) 表示以 0…L-1 号顶点为中间点时的最短路径，刚好符合 Floyd 算法最外层循环到 k=L 时的情况，则此时对 M 和 N 循环所有编号小于 L 的顶点组合即可找到最大编号为 L 的最小环。再经过最外层 k 的循环，即可找到整个图的最小环。
     
 
 ```
 #include <iostream>
#define INF 0x3f3f3f3f
using namespace std;
const int maxn = 150;
int n,m,a,b,c;
int mp[maxn][maxn];//表示的正常从u到v经过k的最短路
int A[maxn][maxn];//表示的是不经过k的时候回来的时候的最短路
int floyd()
{
    int retmin = INF;
    for(int k = 1;k <= n;k++)
    {
        for(int i = 1;i < k;i++)//假设k为最大的结点，进行遍历优化，并且最后也不会包含最大的结点n
        {
            for(int j = i + 1;j < k;j++)
            {
                //为什么不更新优化mp数组呢，是因为这是一个暴力的循环，总能够找到最小值！
                int tmp = A[i][j] + mp[i][k] + mp[k][j];
                //这个时候A[i][j]还没有更新k结点！！因为下一层才开始更新……
                if(tmp < retmin)retmin = tmp;
            }
        }
        for(int i = 1;i <= n;i++)
        {
            for(int j = 1;j <= n;j++)
            {
                if(A[i][j] > A[i][k] + A[k][j])
                    A[i][j] = A[i][k] + A[k][j];
            }
        }
    }
    return retmin;
}
int main()
{
    int i,j;
    while(~scanf("%d%d",&n,&m))
    {
        //初始化
        for(int i = 1;i <= n;i++)
        {
            for(int j = 1;j <= n;j++)
            {
                mp[i][j] = A[i][j] = INF;
            }
        }
        //输入距离进行更新，防止重边的影响，自动定义为双向边
        for(int i = 1;i <= m;i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            mp[a][b] = mp[b][a] = A[a][b] = A[b][a] = min(mp[a][b],c);
        }
        //进行floyd算法，寻找最小环
        int s = floyd();
        if(s == INF)
            printf("It's impossible.\n");
        else
            printf("%d\n",s);
    }
    return 0;
   ```
