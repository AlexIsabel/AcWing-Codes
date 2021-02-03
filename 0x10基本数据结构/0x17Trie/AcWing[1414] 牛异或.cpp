#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100010, M = N * 21;

int n, sum[N], trie[M][2], idx, id[M];

void Insert(int x, int k)
{
	int p = 0;
	for (int i = 20; ~i; i--) {
		int &s = trie[p][x >> i & 1];
		if (!s) s = ++idx;
		p = s;
	}
	id[p] = k;
}

int Query(int x)
{
	int p = 0;
	for (int i=20; ~i; i--){
		int s = x >> i & 1;
		if (trie[p][!s]) p = trie[p][!s];
		else p = trie[p][s];
	}	
	return id[p];
}

int main()
{
	scanf("%d", &n);
	for (int i=1; i<=n; i++) {
		scanf("%d", &sum[i]);
		sum[i] ^= sum[i-1];
	}
	
	int res = -1, a, b;
	Insert(sum[0], 0); 	// 前缀和的 0 号元素不可以省略 
	for (int i=1; i<=n; i++){
		int k = Query(sum[i]);
		int t = sum[i] ^ sum[k];
		if (t > res) res = t, a = k+1, b = i;
		Insert(sum[i], i);	// 保证最节点尽量靠后 
	} 
	printf("%d %d %d\n", res, a, b);
	return 0;	
} 
