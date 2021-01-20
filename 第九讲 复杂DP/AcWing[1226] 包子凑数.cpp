#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int N= 10010;
int n, a[110];
bool f[110][N];
 
int gcd(int a, int b){
	return b ? gcd(b, a%b) : a;
}

int main()
{
	memset(f, 0, sizeof f);
	scanf("%d", &n);
	int d = 0;
	for (int i=1; i<=n; i++){
		scanf("%d", &a[i]);
		d = gcd(d, a[i]);
	}
	if (d != 1) puts("INF");
	else {
		f[0][0] = true;
		for (int i=1; i<=n; i++)
		for (int j=0; j<N; j++){
			f[i][j] = f[i-1][j];
			if (j >= a[i]) f[i][j] |= f[i][j-a[i]];
		} 
		int res = 0;
		for (int i=1; i<N; i++) 
			if (!f[n][i]) res++;
		cout << res << endl;
	}
	
	return 0;
 } 
