/*
	AcWing 2234. 多源汇最大流
*/ 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10010, M = (1e5 + N) * 2, INF = 1e8;

int n, m, S, T;
int a[N], v[M], f[M], nex[M], tot;
int q[N], d[N], curr[N];

void addEdge(int from, int to, int val) {
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
		int u = q[hh++];
		for (int i=a[u]; ~i; i=nex[i])
		{
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
	int res=0, flow;
	while (bfs()) while (flow = find(S, INF)) res += flow;
	return res;
}

int main()
{
    int sc, tc;
    scanf("%d%d%d%d", &n, &m, &sc, &tc);
    S = 0, T = n + 1;
    memset(a, -1, sizeof a);
    for (int i=1; i<=sc; i++) {
        int x;
        scanf("%d", &x);
        addEdge(S, x, INF);
    }
    for (int i=1; i<=tc; i++) {
        int x;
        scanf("%d", &x);
        addEdge(x, T, INF);
    }

    for (int i=1; i<=m; i++) {
        int from, to, flow;
        scanf("%d%d%d", &from, &to, &flow);
        addEdge(from, to, flow);
    }

    printf("%d\n", dinic());
    return 0;
}

