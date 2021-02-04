#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

char get(int x){
	if (x <= 9) return x + '0';
	return x - 10 + 'A';
}

string base(int n, int b){
	string num;
	while (n) num += get(n%b), n /= b;
	reverse(num.begin(), num.end());
	return num;
}

bool check(string num){
	for(int i=0, j = num.size()-1; i<j; i++,j--)
		if (num[i] != num[j]) return false;
	return true;
} 

int main()
{
	int b;
	cin >> b;
	for (int i=1; i<=300; i++){
		string num = base(i*i, b);
		if (check(num)) 
			cout << base(i, b) << " " << num << endl;
	}
	return 0;
}
