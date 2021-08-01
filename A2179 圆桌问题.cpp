/*
	A2179. 圆桌问题
	网络流转化 
*/ 

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 430, M = (150*270 + N)*2, INF = 1e8;

int n, m, S, T;
int a[N], v[M], f[M], nex[M], tot;
int q[N], d[N], curr[N];

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
		int u = q[hh++];
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
	for (int i=curr[u]; ~i && flow < limit; i=nex[i]){
		curr[u] = i;
		int to = v[i];
		if (d[to] == d[u] + 1 && f[i]) {
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
	while(bfs()) 
		while (flow = find(S, INF)) {
			//cout << "flow: " << flow << endl; 
			res += flow;
		}
	return res;
}

int main()
{
	scanf("%d%d", &m, &n);
	S = 0, T = m + n + 1;
	memset(a, -1, sizeof a);
	
	int sum = 0;
	for (int i=1; i<=m; i++) {
		int c;
		scanf("%d", &c);
		addEdge(S, i, c);
		sum += c;
	}
	for (int i=1; i<=n; i++) {
		int c;
		scanf("%d", &c);
		addEdge(m + i, T, c);
	}
	for (int i=1; i<=m; i++)
		for (int j=1; j<=n; j++)
			addEdge(i, m+j, 1);
	
	
	if (dinic() != sum) puts("0");
	else {
		puts("1");
		for (int i=1; i<=m; i++)
		{
			for (int j=a[i]; ~j; j=nex[j])
				if (v[j] > m && v[j] <= m + n && !f[j])
					printf("%d ", v[j] - m);
			puts("");
		}
	}
	return 0;
}



