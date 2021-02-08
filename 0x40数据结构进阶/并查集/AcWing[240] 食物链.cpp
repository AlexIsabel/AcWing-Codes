// 扩展域 -- 拆点
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5e4 + 10;

int n, k, fa[3*N];
int ans;

int Find(int u) {	return (fa[u] == u) ? u : fa[u] = Find(fa[u]); 	}

void UnionSet(int a, int b){	fa[a] = Find(b);	}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i=1; i<=n*3; i++) fa[i] = i;
	
	int d, x, y;
	ans = 0;
	while (k--){
		cin >> d >> x >> y;	
		if (x > n || y > n) {
			ans++;
			continue;
		}
		if (x == y){
			if (d == 2) ans++;	// 单独写是因为 如果 d==1 && x == y 对于 * 会判断错误 
			continue;
		}
		int x_food = x + n, x_enemy = x + 2*n;
		int y_food = y + n, y_enemy = y + 2*n;
		if (Find(y_food) == Find(x)) {	// * Y eat X 
			ans++;
			continue;
		} else if (d == 1) {	// 同类 
			if (Find(x) == Find(y_enemy)) ans++;
			else {
				UnionSet(x, y);
				UnionSet(x_food, y_food);
				UnionSet(x_enemy, y_enemy);
			} 
		} else if (d == 2){		// X eat Y 
			if (Find(x) == Find(y) || Find(y_food) == Find(x) ) ans++;
			else {
				UnionSet(x, y_enemy);
				UnionSet(x_food, y);
				UnionSet(x_enemy, y_food);
			}
		}
	}
	cout << ans << endl;
	return 0;	
} 



//这里我们将三个域,分别转化为了n,n+n,n+n+n.因为读入方面特别烦.
#include <bits/stdc++.h>
using namespace std;
int fa[200000];
int n,m,k,x,y,ans;
int get(int x)
{
    if(x==fa[x]) 
        return x;
    return fa[x]=get(fa[x]);
}
void merge(int x,int y)
{
    fa[get(x)]=get(y);
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=3*n;i++) 
        fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&k,&x,&y);
        if(x>n || y>n) 
            ans++;
        else if(k==1)
        {
            if(get(x)==get(y+n) || get(x)==get(y+n+n)) //如果x,y是同类,但是x是y的捕食中的动物,或者x是y天敌中的动物,那么错误.
                ans++;
            else
            {
                merge(x,y);
                merge(x+n,y+n);
                merge(x+n+n,y+n+n);
            }
        }
        else
        {
            if(x==y || get(x)==get(y) || get(x)==get(y+n)) //x就是y,或者他们是同类,再或者是y的同类中有x
                ans++;//都是假话
            else
            {
                merge(x,y+n+n);//y的捕食域加入x
                merge(x+n,y);//x的天敌域加入y
                merge(x+n+n,y+n);//x的捕食域是y的同类域.
            }
        }
    }
    cout<<ans<<endl;
}
//x是同类域.
//x+n是捕食域
//x+n+n是天敌域

作者：秦淮岸灯火阑珊
链接：https://www.acwing.com/solution/AcWing/content/1007/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。




