#include <iostream>
#include <cmath>
using namespace std;

const int N = 3e4 + 10;

int fa[N], num[N], dis[N], n;

int Find(int u)
{
	if (fa[u] == u) return u;
	int head = Find(fa[u]);
	dis[u] += dis[fa[u]];
	return fa[u] = head;
}

void UnionSet(int i, int j)	// i 接在 j 后 
{
	int headJ = Find(j);
	int headI = Find(i);
	dis[headI] = num[headJ]; 
	num[headJ] += num[headI];
	fa[headI] = headJ;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin >> T;
	char op;
	int i, j;
	for (int i=1; i<=N; i++) fa[i] = i, num[i] =1;
	while (T--){
		cin >> op >> i >> j;
		if (op == 'M'){
			UnionSet(i, j); // 顺序一定是 i, j 
		}
		if (op == 'C'){
			if (Find(i) != Find(j)) cout << "-1\n";
			else cout << abs(dis[i] - dis[j]) - 1 << endl;
		}
	}
	return 0;
 } 
