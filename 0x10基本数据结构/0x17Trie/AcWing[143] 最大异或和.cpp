#include <cstdio>
#include <iostream>

using namespace std;

const int N = 100010, M = 3100010;
int n;
int trie[M][2], idx=0;
int a[N]; 

void Insert(int x)
{
	int p = 0;
	for (int i=30; ~i; i--) { // ~i <=> i>=0 -1��Դ��ȫ��1 
		int &s = trie[p][x >> i & 1];
		if (!s) s = ++idx;
		p = s; 
	}
}

int Query(int x)
{
	int p = 0, res = 0;
	for (int i=30; ~i; i--){
		int s = x >> i & 1;
		if (trie[p][!s]){
			res += (1 << i);
			p = trie[p][!s];
		} else p = trie[p][s];	
		// û��Ҫ�жϴ�ʱP�Ƿ�Ϊ�գ���Ϊ30��ѭ����С 
	}
	return res;
}

int main()
{
	cin >> n;
	for (int i=1; i<=n; i++) {
		cin >> a[i];
		Insert(a[i]);
	}
	int res = 0;
	for (int i=1; i<=n; i++) res = max(res, Query(a[i]));
	cout << res << endl;
	return 0;
}
