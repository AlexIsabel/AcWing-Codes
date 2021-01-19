#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;

const long long N = 100010;

long long n;
long long w[N], a[N], nex[2*N], v[2*N], cnt;
long long f[N]; 

void add(long long fr, long long to) {
	v[++cnt] = to, nex[cnt] = a[fr], a[fr] = cnt;
}

void dfs(long long u, long long fa)
{
	f[u] = w[u];
	for (long long i=a[u]; i; i=nex[i]){
		if (v[i] != fa) {
			dfs(v[i], u);
			f[u] += max(0ll, f[v[i]]);
		}
	}
}

int main()
{
	cin >> n;
	long long fr, to;
	for (long long i=1; i<=n; i++) cin >> w[i];
	for (long long i=1; i<n; i++){
		cin >> fr >> to;
		add(fr, to); 	add(to, fr);
	}
	dfs(1, 0);
	long long ans = f[1];
	for (long long i=2; i<=n; i++) ans = max(ans, f[i]); 
	cout << ans << endl;
	return 0;
 } 
