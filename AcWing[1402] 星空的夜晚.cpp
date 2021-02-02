#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

#define x first
#define y second

using namespace std;

const int N = 110;
const double EPS = 1e-6;

typedef pair<int, int> PII;

int n, m;
char g[N][N];
PII q[N * N];
int top;

double GetDist(PII a, PII b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}

double GetHash()
{
	double sum = 0;
	for (int i=0; i<top; i++)
		for (int j=i+1; j<top; j++){
			sum += GetDist(q[i], q[j]);
		}
	return sum;
} 

char GetId(double key)
{
	static double hash[30];	
	static int id = 0;		// 静态变量编译前及声明
	for (int i=0; i<id; i++)
		if (fabs(hash[i] - key) < EPS)
			return i + 'a';
	hash[id++] = key; 
	return id - 1 + 'a';
}

void Dfs(int a, int b)
{
	q[top++] = {a, b};
	g[a][b] = '0';
	for (int x = a-1; x<=a+1; x++)
	for (int y = b-1; y<=b+1; y++){
		if (x == a && y == b) continue;
		if (x >= 0 && x < n && y >= 0 && y < m && g[x][y] == '1')
			Dfs(x, y);
	}
}

int main()
{
	cin >> m >> n;
	for (int i=0; i<n; i++) cin >> g[i];
	
	for (int i=0; i<n; i++)
	for (int j=0; j<m; j++)
		if (g[i][j] == '1'){
			top = 0;
			Dfs(i, j);
			char c = GetId(GetHash());
			for (int k=0; k<top; k++) 
				g[q[k].x][q[k].y] = c;
		}
	
	for (int i=0; i<n; i++) cout << g[i] << endl; 
	
	return 0;
}

