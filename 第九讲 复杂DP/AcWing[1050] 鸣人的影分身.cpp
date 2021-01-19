#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 11;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n,m;
		scanf("%d %d", &m, &n);
		
		int f[N][N] = {0};
		f[0][0] = 1;
		for (int i=0; i<=m; i++) 
		for (int j=1; j<=n; j++){
			f[i][j] = f[i][j-1];
			if (i >= j) f[i][j] += f[i-j][j];
		}	
		
		cout << f[m][n] << endl;
	}
	return 0;
}
 
