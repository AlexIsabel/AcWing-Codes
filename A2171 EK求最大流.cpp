#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1010, M = 20010, INF = 1e8 + 10;

int n, m, S, T;
int a[N], v[M], nex[M], f[M], tot;
int q[N], d[N], pre[M];
bool st[N];

void addEdge(int from, int to, int val){
	v[tot] = to, nex[tot] = a[from], f[tot] = val, a[from] = tot++;
	v[tot] = from, nex[tot] = a[to], f[tot] = val, a[to] = tot++; 
} 

bool bfs()
{
	int hh = 0, tt = 0;
	memset(st, 0, sizeof st);
	q[0] = S, st[S] = true, d[S] = INF;
	while (hh <= tt) {
		int u = q[hh++];
		for (int i=a[u]; ~i; i=nex[i]) {
			int to = v[i];
			if (!st[to] && f[i]) {
				d[to] = min(f[i], d[u]);
				st[to] = true;
				pre[to] = i;
				if (to == T) return true;
				q[++ tt] = to; 
			}
		}
	}
	return false;
}

int EK()
{
	int res = 0;
	while (bfs())
	{
		res += d[T];
		for (int i=T; i!=S; i=v[pre[i] ^ 1])
			f[pre[i]] -= d[T], f[pre[i] ^ 1] += d[T];
	}
	return res;
}

int main()
{
	scanf("%d %d %d %d", &n, &m, &S, &T);
	memset(a, -1, sizeof a);
	for (int i=1; i<=m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		addEdge(a, b, c);
	}
	cout << EK() << '\n';
	return 0;	
} 
 
 
