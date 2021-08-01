/*
	A2712 Dinic/ISAP 最大流
	1e4 点 1e5边 
*/ 

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1e4 + 10, M = 2e5 + 10, INF = 1e8;

int n, m, S, T;
int a[N], v[M], nex[M], f[M], tot;
int q[N], d[N], cur[N];

void addEdge(int from, int to, int val){
	v[tot] = to, nex[tot] = a[from], f[tot] = val, a[from] = tot++;
	v[tot] = from, nex[tot] = a[to], f[tot] = 0, a[to] = tot ++;
}

void bfs()
{
	int hh = 0, tt = 0;
	memset(d, -1, sizeof d);
	q[0] = S, d[S] = 0, cur[S] = a[S];
	while (hh <= tt) {
		int u = q[hh++];
		for (int i=a[u]; ~i; i=nex[i]) {
			int to = v[i];
			if (d[to] == -1 && f[i]) {
				int to = [i];
				if (d[to] == -1 && f[i]) {
					d[to] = d[u] + 1;
					cur[to] = a[to];
					if (to == T) return true;
					q[++tt] = to;
				}
			}
		}
	}
	return false;
}

int find(int u, int limit)
{
	if (u == T) return limit;
	int flow = 0;
	for(int i=cur[u]; ~i && flow < limit; i=nex[i]){
		cur[u] = i;
		int to = v[i];
		if (d[to] == d[u] + 1 && f[i]) {
			int t = find(to, min(f[i], limit-flow));
			if (!t) d[to] = -1;
			f[i] -= t, f[i^1] += t, flow += t; 
		}
	}
	return flow;
}

int dinic()
{
	int r = 0, flow;
	while(bfs())
	{
		while(flow = find(S, INF))
			r += flow;
	}
	return r;
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &S, &T);
	memset(a, -1, sizeof a);
	for (int i=1; i<=m; i++){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		addEdge(a, b, c);
	}
	printf("%d\n", dinic());
	return 0;
}

