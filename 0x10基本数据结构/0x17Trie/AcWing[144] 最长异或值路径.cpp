#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100010;

int n;
int a[N], nex[N*2], v[N*2], w[N*2], tot;
int d[N], trie[31*N][2], idx;

void AddEdge(int from, int to, int value){
	nex[++tot] = a[from], v[tot] = to, w[tot] = value, a[from] = tot; 	
}

void Dfs(int u, int  fa)
{
	for (int i=a[u]; i; i=nex[i]){
		int to = v[i];
		if (v[i] == fa) continue;
		d[to] = d[u] ^ w[i];
		Dfs(to, u);
	}
}

void Insert(int x)
{
	int p = 0;
	for(int i=30; ~i; i--){
		int &s = trie[p][(x >> i) & 1];
		if (!s) s = ++idx;
		p = s; 
	}
}

int Query(int x)
{
	int p = 0, res = 0;
	for (int i=30; ~i; i--) {
		int s = (x >> i) & 1;
		if (trie[p][!s]){
			if (!s)  res += (1<<i);
			p = trie[p][!s];
		} else p = trie[p][s], res += ((s) ? (1<<i) : 0);
	}	
	return res;
}

int main()
{
	ios::sync_with_stdio(false);	
	cin >> n;
	int from, to, value;
	for (int i=1; i<n; i++){
		cin >> from >> to >> value;
		from++, to++; 
		AddEdge(from, to, value);
		AddEdge(to, from, value);
	}
	Dfs(1, 0);   // 1 .. n 号点, 为了d[0] = 0 
	
//	for (int i=1; i<=n; i++) cout << d[i] << " "; cout << endl;
	
	// d[u]  u 到 root 的路径异或和, 
	// d(u, lca) ^ d(lca, v) = d(u, lca) ^ d(lca, root) ^ d(root, lca) ^ d(lca, v) 
	// caz  d(lca, root) ^ d(root, lca) = 0, and 0 ^ x = x 
	// so d(u, lca) ^ d(lca, v) = d(u, root) ^ d(root, v) = d[u] ^ d[v] 
	for (int i=1; i<=n; i++) Insert(d[i]);
	int res = -1;
	for (int i=1; i<=n; i++) {
		int t = Query(d[i]);
		int temp = t ^ d[i]; 
	//	cout << d[i] << " " << t << " " << temp << endl;
		if (temp > res) res = temp;   // t 必不为 d[i] 本身，因为 x ^ x = 0 
		// ^ 的运算比较级小于 >， 写成 t ^ d[i] > res 会出错 
	}
	cout << res << endl;
	return 0;
} 
