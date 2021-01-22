#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
const int N = 25;

int n, m;
char g[N][N];

int bfs(int sx, int sy)
{
    queue <PII> q;
    q.push({sx, sy});
    g[sx][sy] = '#';
    int res = 0;
    int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
    while (q.size()){
        auto t = q.front();
        q.pop();
        res++;
        
        for (int i=0; i<4; i++) {
            int x = t.x + dx[i], y = t.y + dy[i];
            if ( x < 0 || x >= n || y < 0 || y >= m || g[x][y] != '.') continue;
            g[x][y] = '#';
            q.push({x, y});

        }
    }
    
    return res;    
}


int main()
{
    while (cin >> m >> n, n || m){
        for (int i=0; i<n; i++) cin >> g[i];
        int x,  y;
        for (int i=0; i<n; i++) 
        for (int j=0; j<m; j++)
            if (g[i][j] == '@'){
                x = i;
                y = j;
            }
        cout << bfs(x, y) << endl;
    }
    
    return 0;
}
