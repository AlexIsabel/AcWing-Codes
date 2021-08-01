/*
	A3188 manacher算法
	注意 mr max_right 下标为开区间 
	主要思想：通过补充字符将奇偶两种情况都转化为奇数，即都有对称轴 
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 2e7 + 10;

int n;
char a[N], b[N];
int p[N];

void init()
{
	int k = 0;
	b[k++] = '$', b[k++] = '#';
	for (int i=0; i<n; i++) 
		b[k++] = a[i], b[k++] = '#';
	b[k++] = '^';
	n = k;
}

void manacher()
{
	// mr 是右端的闭区间 
	int mr = 0, mid;
	for (int i=1; i<n; i++) 
	{
		if (i < mr) p[i] = min(p[mid*2 - i], mr-i);
		else p[i] = 1;
		
		while (b[i-p[i]] == b[i+p[i]]) p[i]++;
		
		if (i+p[i] > mr) mr = i + p[i], mid = i;
	}
}
 
int main()
{
	scanf("%s", a);
	n = strlen(a);
	
	init();
	manacher();
	
	int res = 0;
	for (int i=0; i<n; i++) res = max(res, p[i]);
	printf("%d\n", res-1);
	return 0;
}
