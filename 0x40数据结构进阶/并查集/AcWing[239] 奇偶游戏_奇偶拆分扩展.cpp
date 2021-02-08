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
	ios::sync_with_stdio(false);
	cin >> n >> m;
	char str[5];
	for (int i=1; i<= m; i++) {
		cin >> query[i].l >> query[i].r >> str;
		query[i].ans = (str[0] == 'o') ? 1 : 0;
		a[++cnt] = query[i].l - 1, a[++cnt] = query[i].r;
	}
	sort(a+1, a+cnt+1);
	n = unique(a+1, a+cnt+1) - a - 1;
}

int Find(int u) {	return (u == fa[u])? u : fa[u] = Find(fa[u]); }

int main()
{
	ReadDiscrete();
	for (int i=1; i<=2*n; i++) fa[i] = i;
	
	int x, y, x_odd, x_even, y_odd, y_even, p, q;
	int res = m;
	for (int i=1; i<=m; i++){
		x = lower_bound(a+1, a+n+1, query[i].l - 1) - a;
		y = lower_bound(a+1, a+n+1, query[i].r) - a;
		x_odd = x, x_even = x + n;
		y_odd = y, y_even = y + n;
		if (query[i].ans == 0){		// ÆæÅ¼ÐÔÒ»ÖÂ
			 p = Find(x_odd), q= Find(y_even);
			 if (p == q) {
			 	res = i - 1;
			 	break;
			 }
			 fa[p] = Find(y_odd);
			 fa[Find(x_even)] = q; 
		} else {
			p = Find(x_odd), q = Find(y_odd);
			if (p == q) {
				res = i - 1;
				break;
			}
			fa[p] = Find(y_even);
			fa[Find(x_even)] = q;
		}
	}
	
	cout << res << endl;
	return 0;	
} 




