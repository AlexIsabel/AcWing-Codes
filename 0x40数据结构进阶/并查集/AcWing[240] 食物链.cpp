// ��չ�� -- ���
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
			if (d == 2) ans++;	// ����д����Ϊ ��� d==1 && x == y ���� * ���жϴ��� 
			continue;
		}
		int x_food = x + n, x_enemy = x + 2*n;
		int y_food = y + n, y_enemy = y + 2*n;
		if (Find(y_food) == Find(x)) {	// * Y eat X 
			ans++;
			continue;
		} else if (d == 1) {	// ͬ�� 
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



//�������ǽ�������,�ֱ�ת��Ϊ��n,n+n,n+n+n.��Ϊ���뷽���ر�.
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
            if(get(x)==get(y+n) || get(x)==get(y+n+n)) //���x,y��ͬ��,����x��y�Ĳ�ʳ�еĶ���,����x��y����еĶ���,��ô����.
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
            if(x==y || get(x)==get(y) || get(x)==get(y+n)) //x����y,����������ͬ��,�ٻ�����y��ͬ������x
                ans++;//���Ǽٻ�
            else
            {
                merge(x,y+n+n);//y�Ĳ�ʳ�����x
                merge(x+n,y);//x����������y
                merge(x+n+n,y+n);//x�Ĳ�ʳ����y��ͬ����.
            }
        }
    }
    cout<<ans<<endl;
}
//x��ͬ����.
//x+n�ǲ�ʳ��
//x+n+n�������

���ߣ��ػ����ƻ���ɺ
���ӣ�https://www.acwing.com/solution/AcWing/content/1007/
��Դ��AcWing
����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������




