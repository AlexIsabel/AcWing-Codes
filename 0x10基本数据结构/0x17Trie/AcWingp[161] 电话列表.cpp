#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010;

int trie[10*N][10], idx; 
//int num;
char num[12];
bool finish[10*N];

bool InsertAndFind()
{
//	int base = 1;
//	while (num / (base * 10) > 0) base *= 10;
	
	bool changed = false;
	int p = 0;
//	for (; base; num%=base, base/=10){
//		int u = num / base;
	for (int i=0; num[i]>='0' && num[i] <= '9'; i++){
		int u = num[i] - '0';
		if (!trie[p][u]) {
			trie[p][u] = ++idx;
			changed = true;
		} 
		p = trie[p][u];
		if (finish[p]) return true;
	} finish[p] = true;
	
	return !changed;
}

int main()
{

	int T, n;
	bool f = true;
	cin >> T;
	while (T--){
		cin >> n;
		memset(finish, 0, sizeof finish); // 多组测试记得初始化 
		memset(trie, 0, sizeof trie);
		idx = 0;	// 初始化 
		f = true;	// 初始化 
		for (int i=1; i<=n; i++) {
			scanf("%s", num);
			if (InsertAndFind()) {
				f = false;
				for (int j= i+1; j<=n; j++) cin >> num;
				break;
			}
		}
		cout << (f ? "YES" : "NO") << endl;
	}
	return 0;
}
