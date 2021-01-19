#include<cstdio>
#include<cstring>
using namespace std;

const int N = 1010;

char s[N];
int f[N][N];


int main()
{
	scanf("%s", s);
	int len = strlen(s);
	
	for (int l=1; l<=len; l++)
	for (int st=0; st+l-1 < len; st++){
		int ed = st+l-1;
		if (l == 1) f[st][ed] = 1;
		else {
			// when s[n] == s[n+1], f[n][n+1] = [n+1][n] + 2
			// f[n+1][n] is 0, because l = n+1 > r = n  
			if (s[st] == s[ed]) f[st][ed] = f[st+1][ed-1] + 2;
			else {
				if (f[st+1][ed] > f[st][ed]) f[st][ed] = f[st+1][ed];
				if (f[st][ed-1] > f[st][ed]) f[st][ed] = f[st][ed-1];
			}
		} 		
	}
	printf("%d\n", len - f[0][len-1]);
	return 0;	
} 
