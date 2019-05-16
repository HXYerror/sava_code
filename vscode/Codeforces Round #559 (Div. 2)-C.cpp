//#include<bits/stdc++.h>
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
#include <queue>
#include <stack>
#define LL long long
using namespace std;
const int MAX = 300010;
const int MAX_1 = 55;
const int INF = 0xfffffff;//268435455,2e8;
const double EPS = 0.0000001;
const int MOD = 10000007;
int T,N,M;


/*-------------------------------------------------------------------------------------------*/
struct Man
{
    LL x;
    LL sum;
    int cnt;
    int m;
}man[MAX];
int won[MAX];
/* ------------------------------------------------------------------------------------------*/

bool Cmp(Man a,Man b)
{
    return a.x < b.x;
}

int main()
{
    //std::ios::sync_with_stdio(false);
    //cin.tie(0);
    //cout.tie(0);
    //freopen("input.in","r",stdin);
    //freopen("output.out","w",stdout);
/* --------------------------------------------------------------------------------------*/
    cin >> N >> M;
    LL ma = 0;
    int mi = INF;
    int flagm = 0;
    int flag = 0;
    for(int i = 1;i <= N;i++)
    {
        cin >> man[i].x;
        ma = max(man[i].x,ma);
        if(man[i].x) flagm = 1;
    }
    for(int i = 1;i <= M;i++)
    {
        cin >> won[i];
        mi = min(mi,won[i]);
        if(!won[i]) flag = 1;
    }
    if((flag && flagm) || (ma > mi))
    {
        cout << -1 << endl;
        return 0;
    }
    sort(man+1,man+N+1,Cmp);
    sort(won+1,won+M+1,greater<int>());
    bool f = false;


    for(int i = 1;i <= M;i++)
    {
        //won[i];
        Man temp;
        temp.x = won[i];
        auto it = lower_bound(man+1,man+N,temp,Cmp);
        //cout << won[i] << " "<<it->cnt << " " <<it->x<< " "<< it->sum <<endl;
        for(;it != &man[0];it--)
        {
            if(it->cnt == M - 1 && !it->m && won[i] != it->x)
            {
                //cout << "QAQ" <<endl;
                continue;
            }
            it->sum += won[i];
            if(it->x == won[i]) it->m = 1;
            it->cnt++;
            //cout << won[i] << " "<<it->cnt << " " <<it->x<< " "<< it->sum <<endl;
            break;
        }
        if(it == &man[0]) f = true;
    }

    if(f)
    {
        cout << "-1" <<endl;
        return 0;
    }
    LL ans = 0;
    for(int i = 1;i <= N;i++)
    {
        ans += man[i].sum;
        ans += (M - man[i].cnt) * man[i].x;
       // cout << man[i].sum << " " << man[i].cnt << " "<<man[i].x << " " << ans <<endl;
    }
    cout << ans;
    return 0;
}