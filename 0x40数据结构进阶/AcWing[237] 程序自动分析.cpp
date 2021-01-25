// 题解 STL unordered_map 
// unoredered_map 内部封装的是 Hash；map 内部封装的红黑树

#include <iostream>
#include <cstdio>
#include <unordered_map>	// C++ 11 
#pragma GCC optimize(2)
using namespace std;

const int N = 1e6 * 2 + 10;
int a[N][3], n, m;
int cnt, t, fa[N], ms[N];

unordered_map<int, int> c;

int Find(int u) {
	return (fa[u] == u) ? u : fa[u] = Find(fa[u]);
}

void UnionSet(int a, int b){
	fa[Find(fa[a])] = Find(fa[b]);
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n;	
		n *= 3;
		int x;
		for (int i=1; i<=n; i++) {
			cin >> x;
			if (i%3){
				if (c[x] == 0) c[x] = (++cnt);
				a[i/3 + 1][i%3] = c[x];
				fa[c[x]] = c[x]; 
			} else ms[i/3] =  x;
		}
		bool f = true;
		for (int i=1; i<=n/3; i++) {
			if (ms[i]) UnionSet(a[i][1], a[i][2]);
		}
		for (int i=1; i<=n/3; i++)
			if (!ms[i]) {
				if (Find(a[i][1]) == Find(a[i][2])) {
					f = false;
					break;
				}
			}
		cout << ( (f)? "YES" : "NO" ) << endl;
	}
	
	return 0;	
} 
