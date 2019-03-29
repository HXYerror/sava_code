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
//<< fixed << setprecision(n) 保留小数
using namespace std;

int pre[600];
int flag[600];
int root[600];

int find_(int n)
{
    if(pre[n] == n) return n;
    else return find_(pre[n]);
}

int main()
{
    for(int i = 0;i < 600;i++)
    {
        root[i] = -1;
        pre[i] = i;
    }

    int n,m;
    cin >> n >> m;
    while(m--)
    {
        int a,b;
        cin >> a >> b;
        pre[a] = b;
    }
    int k = 0;
    for(int i = 0;i < n;i++)
    {
        int f = find_(i);
        if(root[f] == 0) root[k++] = f;
    }


    return 0;
}


