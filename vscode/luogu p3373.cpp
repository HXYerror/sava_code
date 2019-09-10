// luogu-judger-enable-o2
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
#include <deque>
#include <utility>
#define ll long long
using namespace std;
const int MAX = 100010;//100000
const int MAX_1 = 2;
const int MAX_2 = 1000010;
const int INF = 0x3f3f3f3f;//1061109567,1e9,int-MAX2147483647;
const double EPS = 0.0000001;
const int MOD = 998244353;//998244353;
const double PI = acos(-1);
ll T,N,M,K;

/*---------------------------------------------------------------------------------------------------*/
//线段树
struct Tree
{
    int l,r;
    ll sum;
    ll lazyadd,lazymul;
}tree[4*MAX];
int a[MAX];
int P;
/* --------------------------------------------------------------------------------------------------*/

void bulid(int pos,int l,int r)
{
    tree[pos].l = l;
    tree[pos].r = r;
    if(l == r)
    {
        tree[pos].sum = a[l];
        tree[pos].lazymul = 1;
        return;
    }
    int mid = (l+r)>>1;
    bulid(pos<<1,l,mid);
    bulid(pos<<1|1,mid+1,r);
    tree[pos].sum = tree[pos<<1].sum + tree[pos<<1|1].sum;
    tree[pos].lazymul = 1;
}

void pushdown(int pos)
{
    tree[pos<<1].sum = (tree[pos<<1].sum * tree[pos].lazymul) % P;
    tree[pos<<1|1].sum = (tree[pos<<1|1].sum * tree[pos].lazymul) % P;
    tree[pos<<1].sum = (tree[pos<<1].sum + tree[pos].lazyadd*(tree[pos<<1].r - tree[pos<<1].l + 1)) % P;
    tree[pos<<1|1].sum = (tree[pos<<1|1].sum + tree[pos].lazyadd*(tree[pos<<1|1].r - tree[pos<<1|1].l + 1)) % P;

    tree[pos<<1].lazyadd = (tree[pos<<1].lazyadd*tree[pos].lazymul) % P;
    tree[pos<<1|1].lazyadd = (tree[pos<<1|1].lazyadd*tree[pos].lazymul) % P;
    tree[pos<<1].lazymul = (tree[pos<<1].lazymul*tree[pos].lazymul) % P;
    tree[pos<<1|1].lazymul = (tree[pos<<1|1].lazymul*tree[pos].lazymul) % P;
    tree[pos<<1].lazyadd = (tree[pos<<1].lazyadd + tree[pos].lazyadd ) % P;
    tree[pos<<1|1].lazyadd = (tree[pos<<1|1].lazyadd + tree[pos].lazyadd ) % P;

    tree[pos].lazyadd = 0;
    tree[pos].lazymul = 1;
}

void updateadd(int pos,int l,int r,int x)
{
    if(l <= tree[pos].l && r >= tree[pos].r)
    {
        tree[pos].sum = (tree[pos].sum + (ll)x * (tree[pos].r - tree[pos].l + 1)) % P;
        tree[pos].lazyadd = (tree[pos].lazyadd + x) % P;
        return;
    }
    if(tree[pos].lazyadd || tree[pos].lazymul != 1) pushdown(pos);
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    if(l <= mid) updateadd(pos<<1,l,r,x);
    if(r > mid) updateadd(pos<<1|1,l,r,x);
    tree[pos].sum = (tree[pos<<1].sum + tree[pos<<1|1].sum) % P;
}

void updatemult(int pos,int l,int r,int x)
{
    if(l <= tree[pos].l && r >= tree[pos].r)
    {
        tree[pos].sum = ((ll)x * tree[pos].sum) % P;
        tree[pos].lazymul = (tree[pos].lazymul*x) % P;
        tree[pos].lazyadd = (tree[pos].lazyadd*x) % P;
        return;
    }
    if(tree[pos].lazyadd || tree[pos].lazymul != 1) pushdown(pos);
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    if(l <= mid) updatemult(pos<<1,l,r,x);
    if(r > mid) updatemult(pos<<1|1,l,r,x);
    tree[pos].sum = (tree[pos<<1].sum + tree[pos<<1|1].sum) % P;
}

ll query(int pos,int l,int r)
{
    if(l <= tree[pos].l && r >= tree[pos].r)
    {
        return tree[pos].sum;
    }
    if(tree[pos].lazyadd || tree[pos].lazymul != 1) pushdown(pos);
    int mid = (tree[pos].l + tree[pos].r) >> 1;
    ll ans = 0;
    if(l <= mid) ans += query(pos<<1,l,r);
    ans %= P;
    if(r > mid) ans += query(pos<<1|1,l,r);
    ans %= P;
    return ans;
}


int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //freopen("input.in","r",stdin);
    //freopen("output.out","w",stdout);
/* -----------------------------------------------------------------------------------------*/
    cin >> N >> M >> P;
    for(int i = 1;i <= N;i++)
    {
        cin >> a[i];
    }
    bulid(1,1,N);
    int x,y,z;
    while(M--)
    {
        cin >> x;
        if(x == 1)
        {
            cin >> x >> y >> z;
            updatemult(1,x,y,z);
        }
        else if(x == 2)
        {
            cin >> x >> y >> z;
            updateadd(1,x,y,z);
        }
        else if(x == 3)
        {
            cin >> x >> y;
            cout << query(1,x,y) <<endl;
        }
    }
    return 0;
}
