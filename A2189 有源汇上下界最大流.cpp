/*
    A2189. 有源汇上下界最大流 
    注意与 无源汇 的区别 
*/ 
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 210, M = (N + 1e4) * 2, INF = 1e8;

int n, m, S, T;
int a[N], v[M], nex[M], f[M], tot;
int q[N], d[N], curr[N], A[N]; 

void addEdge(int from, int to, int val){
    v[tot] = to, f[tot] = val, nex[tot] = a[from], a[from] = tot++;
    v[tot] = from, f[tot] = 0, nex[tot] = a[to], a[to] = tot++;
}

bool bfs()
{
    int hh = 0, tt = 0;
    memset(d, -1, sizeof d);
    q[0] = S, d[S] = 0, curr[S] = a[S]; 
    while (hh <= tt)
    {
        int u = q[ hh++ ];
        for (int i=a[u]; ~i; i=nex[i]) {
            int to = v[i];
            if (d[to] == -1 && f[i]) {
                d[to] = d[u] + 1;
                curr[to] = a[to];
                if (to == T) return true;
                q[++tt] = to;
            }
        }   
    }
    return false;
}

int find(int u, int limit)
{
    if (u == T) return limit;
    int flow = 0;

    for (int i=curr[u]; ~i && flow < limit; i=nex[i]) {
        curr[u] = i;
        int to = v[i];
        if (d[to] == d[u] + 1 && f[i])
        {
            int t = find(to, min(f[i], limit - flow));
            if (!t) d[to] = -1;
            f[i] -= t, f[i^1] += t, flow += t;
        }
    } 

    return flow;
}

int dinic()
{
    int res = 0, flow;
    while (bfs()) while (flow = find(S, INF)) res += flow;
    return res; 
}

int main()
{
    int s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    S = 0, T = n + 1;
    memset(a, -1, sizeof a);
    for (int i=1; i<=m; i++) {
        int from, to, lbound, ubound;
        scanf("%d%d%d%d", &from, &to, &lbound, &ubound);
        addEdge(from, to, ubound - lbound);
        A[from] -= lbound, A[to] += lbound;
    }


    int sum = 0;
    for (int i=1; i<=n; i++) 
        if (A[i] > 0) addEdge(S, i, A[i]), sum += A[i];
        else if (A[i] < 0) addEdge(i, T, -A[i]); 

    addEdge(t, s, INF);
    if (dinic() < sum) puts("No Solution");
    else {
        int res = f[tot - 1];
        S = s, T = t;
        f[tot - 1] = f[tot -2] = 0;
        printf("%d\n", res + dinic()); 
    }
    return 0;
}

