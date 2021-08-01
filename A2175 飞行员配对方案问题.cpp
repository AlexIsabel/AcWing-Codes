/*
	A2175. 飞行员配对方案问题
	二分图匹配 
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 210, M = 1e4 + 10, INF = 1e8;

int n1, n2, m, S, T;
int a[N], v[M], nex[M], f[M], tot;
int q[N], d[N], curr[N];

void addEdge(int from, int to, int val){
	v[tot] = to, nex[tot] = a[from], f[tot] = val, a[from] = tot++;
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
    int r = 0, flow;
    while (bfs()) {
    	// cout << "BFS YES\n";
        while (flow = find(S, INF))
            r += flow; 
    }
    return r;
}

int main()
{
	cin >> n1 >> n2;
	S = 0, T = n2 + 1;
	memset(a, -1, sizeof a);
	for (int i=1; i<=n1; i++) addEdge(S, i, 1);
	for (int i=n1+1; i<=n2; i++) addEdge(i, T, 1);
	
	int a, b;
	while (cin >> a >> b, a != -1) addEdge(a, b, 1);
	
	cout << dinic() << '\n';
	for (int i=0; i<tot; i+=2) 
		if (v[i] > n1 && v[i] <= n2 && !f[i]) 
			cout << v[i^1] << ' ' << v[i] << '\n';
	
	return 0;
}





