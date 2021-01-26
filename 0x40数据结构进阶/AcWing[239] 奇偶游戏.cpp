#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2e4 + 10;

int n, m, a[N], fa[N], d[N], cnt;

struct Query{	
	int l, r, ans; 
}query[N/2]; 

void ReadDiscrete()
{
	cin >> n >> m;
	char str[5];
	for (int i=1; i<=m; i++){
		cin >> query[i].l >> query[i].r >> str;
		query[i].ans = (str[0] == 'o') ? 1 : 0;
		a[++cnt] = query[i].l-1, a[++cnt] = query[i].r;
	}
	sort(a+1, a+cnt+1);
	n = unique(a+1, a+cnt+1) - a - 1;
}

int Find(int u) {	
	if (fa[u] == u) return u;
	int root = Find(fa[u]);
	d[u] ^= d[fa[u]];
	return fa[u] = root; 
}

int main()
{
	ios::sync_with_stdio(false);
	
	ReadDiscrete();
	
	for (int i=1; i<=n; i++) fa[i] = i;
	int x, y, p, q, res = m;
	for (int i=1; i<=m; i++){
		x = lower_bound(a+1, a+n+1, query[i].l-1) - a;
		y = lower_bound(a+1, a+n+1, query[i].r) - a;
		p = Find(x), q = Find(y);
		if (p == q) {
			if ((d[x] ^ d[y]) != query[i].ans) {
				res = i - 1;
				break;
			}
		} else fa[p] = q, d[p] = d[x] ^ d[y] ^ query[i].ans;
	}
	
	cout << res << endl;
	return 0;
} 












