#include <iostream>
#include <algorithm>
#include <cstring> 
#include <cstdio>
using namespace std;

const int N = 100010;
const int M = 100010;

struct Edge{
    int v, nex, c;
}e[M*2];
int a[N], tot, n, m, st[N];
bool flag = true;


void addEdge(int from, int to){ e[++tot].v = to, e[tot].nex = a[from], a[from] = tot; }

bool dfs(int u, int tag)
{
    st[u] = tag;
    for (int i=a[u]; i; i=e[i].nex){
        int to = e[i].v;
        if (st[to] == 3 - tag) continue;
        else if (st[to] == tag) return false;
        else if (!dfs(to, 3-tag)) return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int from, to;
    for (int i=1; i<=m; i++) {
        cin >> from >> to;
        if (from == to) continue;
        addEdge(from, to);
        addEdge(to, from);
    }
    for (int i=1; i<=n; i++) {
        if (!st[i]) flag &= dfs(i, 1);
    }
    if (flag) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}
