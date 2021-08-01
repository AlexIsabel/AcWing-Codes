/*
	A2188. 无源汇上下界可行流 
	将边的限制转化为点的限制, 注意边数上界 
*/ 

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
 
const int N = 210, M = (10200 + N) * 2, INF = 1e8;

int a[N], v[M], nex[M], f[M], tot, l[M];
int n, m, S, T, A[N];
int q[N], d[N], curr[M];

void addEdge(int from, int to, int lbound, int ubound){
	v[tot] = to, nex[tot] = a[from], f[tot] = ubound - lbound, l[tot] = lbound, a[from] = tot++;
	v[tot] = from, nex[tot] = a[to], f[tot] = 0, a[to] = tot++; 
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
	
	for (int i=curr[u]; ~i && flow < limit; i=nex[i])
	{
		curr[u] = i;
		int to = v[i];
		if (d[to] == d[u] + 1 && f[i]) {
			int t = find(to, min(limit - flow, f[i]));
			if (!t) d[to] = -1;
			f[i] -= t, f[i^1] += t, flow += t; 
		}
	}
	
	return flow;
}

int dinic()
{
	int res = 0, flow;
	while (bfs())
		while (flow = find(S, INF)) res += flow;
	return res;	
}

int main()
{
	scanf("%d%d", &n, &m);
	S = 0, T = n + 1;
	memset(a, -1, sizeof a);
	for (int i=1; i<=m; i++){
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		addEdge(a, b, c, d);
		A[a] -= c, A[b] += c;
	}
	int sum = 0;
	for (int i=1; i<=n; i++) 
		if (A[i] > 0) addEdge(S, i, 0, A[i]), sum += A[i];
		else if (A[i] < 0) addEdge(i, T, 0, -A[i]);
	
	if (dinic() != sum) puts("NO");
	else {
		puts("YES");
		for (int i=0; i<m*2; i+=2)
			printf("%d\n", f[i^1] + l[i]);
	}
	
	return 0;
}
 
