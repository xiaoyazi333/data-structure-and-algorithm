#include <bits/stdc++.h>

using namespace std;

#define PRINT_ARRAY(a,n)    do{for(int i = 0; i < n; i++) cout<<a[i]<<"|"; cout<<endl;}while(0)

/**********************************************
    无向图的割点&桥 Tarjan算法

**********************************************/

/**********************************************
    1 - 0 -3
    | /    |
    2      4

    割点case1 :0,3
    桥 0-3 3-4
**********************************************/
// #define V (5)
// int g[V][V] = 
// { // 0 1 2 3 4
//     {0,1,1,1,0},
//     {1,0,1,0,0},
//     {1,1,0,0,0},
//     {1,0,0,0,1},
//     {0,0,0,1,0},
// };

/**********************************************
    0 - 1   6  7
    | / |   | /|
    2 - 3 - 4  5

    割点 3,4,7
    桥 3-4 4-7 7-5 4-6
**********************************************/
#define V (8)
int g[V][V] = 
{ // 0 1 2 3 4 5 6 7 
    {0,1,1,0,0,0,0,0},
    {1,0,1,1,0,0,0,0},
    {1,1,0,1,0,0,0,0},
    {0,1,1,0,1,0,0,0},
    {0,0,0,1,0,0,1,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,1,0,0},
};

void tarjan_dfs(int x, int dfn[], int low[], int fa[], bool ap[])
{
    static int times = 1;
    dfn[x] = low[x] = times++;
    int child = 0;
    for(int y = 0; y < V; y++)
    {
        if(g[x][y])
        {
            if(0 == dfn[y])
            {
                child++;
                fa[y] = x;
                tarjan_dfs(y, dfn, low, fa, ap);
                
                if((-1 == fa[x] && child > 1)   
                || (-1 != fa[x] && dfn[x] <= low[y]))
                    ap[x] = true; 
                if(dfn[x] < low[y])
                    cout<<x<<"->"<<y<<" is bridge"<<endl;

                low[x] = min(low[x], low[y]);
            }
            else if(y != fa[x])
                low[x] = min(low[x], dfn[y]);
            }
    }
}

void articulation_point()
{
    bool ap[V];
    int dfn[V], low[V], fa[V];

    bzero(ap, sizeof(ap));
    bzero(dfn, sizeof(dfn));
    bzero(low, sizeof(dfn));
    memset(fa, -1, sizeof(fa));

    for(int i = 0; i < V; i++)
        if(!dfn[i])
            tarjan_dfs(i, dfn, low, fa, ap);

    for(int i = 0; i < V; i++)
        if(ap[i])
            if(-1 == fa[i]) cout<<"cut point ["<<i<<"] : root"<<endl;   
            else            cout<<"cut point ["<<i<<"] : not root"<<endl;

    PRINT_ARRAY(fa, V);
    PRINT_ARRAY(low, V);
}

int main()
{
    articulation_point();

    return 0;
}