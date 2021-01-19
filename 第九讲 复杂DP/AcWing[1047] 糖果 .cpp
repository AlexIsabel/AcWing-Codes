#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 110;
int dp[N][N];

int main()
{
	int n, k, w;
	cin >> n >> k;
	
	memset(dp, -0x7f, sizeof dp);
	
	dp[0][0] = 0;
	for (int i=1; i<=n; i++) {
		cin >> w;
		for (int j=0; j<k; j++) {
			dp[i][j] = max(dp[i-1][j], dp[i-1][(j + k - w%k) % k] + w);
		}	 
	}
	
	cout << dp[n][0] << endl;
	return 0;
}
