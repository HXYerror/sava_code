#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
//<< fixed << setprecision(n) 保留尝数
using namespace std;

const int INF = 666666;
const int MAX = 550;
int flag[MAX];
int dis[MAX];
int road[MAX][MAX];
int value[MAX];
int N,M,S,D;
int f_v[MAX];

int Dijkstra(int x)
{
    for(int i = 0;i < N;i++)
    {
        dis[i] = road[x][i];
        f_v[i] = value[x] + value[i];
    }
    flag[x] = 0;
    for(int i = 0;i < N;i++)
    {
        int min = INF;
        int temp,t_v = -1;
        for(int j = 0;j < N;j++)
        {
            if(flag[j] == 0 && road[i][j] < min)
            {
                temp = j;
                min = road[i][j];
                t_v = value[j];
            }
            else if(flag[j] == 0 && road[i][j] == min)
            {
                if(value[j] > t_v) 
                {
                    temp = j;
                    t_v = value[j];
                }
            }
        }
        flag[temp] = 1;
        for(int j = 0;j < N;i++)
        {
            if(dis[j] > dis[temp] + road[temp][j] && flag[j] == 0)
            {
                dis[j] = dis[temp] + road[temp][j];
                f_v[j] = f_v[temp] + value[j];
            }
            else if(dis[j] == dis[temp] + road[temp][j] && flag[j] == 0)
            {
                if(f_v[j] < f_v[temp] + value[j])
                {
                    f_v[j] = f_v[temp] + value[j];
                }
            }
        }
    }
}

int main()
{
    for(int i = 0;i < 550;i++)
    {
        for(int j = 0;j < 550;j++)
        {
            road[i][j] = INF;
            if(i == j)  road[i][j] = 0;
        }
    }
    cin >> N >> M >> S >> D;
    for(int i = 0;i < N;i++)
    {
        cin >> value[i];
    }
    while(M--)
    {
        int a,b,c;
        cin >> a >> b >> c;
        road[a][b] = c;
        road[b][a] = c;
    }
    Dijkstra(S);
    cout << dis[D] << " " << f_v[D];
    return 0;
}


