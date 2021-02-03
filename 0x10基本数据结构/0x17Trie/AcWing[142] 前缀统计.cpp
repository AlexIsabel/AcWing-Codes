#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1000010, M = 500000;
int n, m;
int trie[M][26], cnt[N], idx;
char str[N];

void Insert()
{
	int p = 0;	// root -> 0号 
	for (int i=0; str[i]; i++){
		int &s = trie[p][str[i] - 'a']; // s 为trie[][]的别名 
		if (!s) s = ++idx;
		p = s;
	}
	cnt[p]++;
}

int Query()
{
	int p = 0, res = 0;
	for (int i=0; str[i]; i++){
		int &s = trie[p][str[i] - 'a'];
		if (!s) break;
		p = s;
		res += cnt[p];
	}
	return res;
}

int main()
{
	scanf("%d %d", &n, &m);
	while (n--){
		scanf("%s", str);
		Insert();
	}
	while (m--){
		scanf("%s", str);
		printf("%d\n", Query());
	}
	return 0;
}
