#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 1e4 + 10;
int n, fa[N];
struct Item{
	int d,p;
}a[N];

bool cmp(Item a, Item b) {
	return a.p > b.p;
}

int Find(int u){ 	return (fa[u] == u) ? u : fa[u] = Find(fa[u]);	}

void UnionSet(int a, int b) {	fa[Find(a)] = Find(b);	}

int main()
{
	while (scanf("%d", &n) != EOF)
	{
		int max_d = 1;
		for(int i=1; i<=n; i++){
			scanf("%d %d", &a[i].p, &a[i].d);
			max_d = max(max_d, a[i].d);
		}
		for (int i=1; i<=max_d; i++) fa[i] = i;
		sort(a+1, a+n+1, cmp);		
		
		int ans = 0;
		int freeDay;
		for (int i=1; i<=n; i++){
			freeDay = Find(a[i].d);
			if (freeDay > 0){
				ans += a[i].p;
				UnionSet(freeDay, freeDay-1);
			}
		}
		
		printf("%d\n", ans);
	}
	return 0;
 } 
