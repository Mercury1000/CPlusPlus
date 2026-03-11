#include<iostream>
#define N 10
using namespace std;


int main()
{
	//方向向量	
	int dy[] = { 1,0,-1,0 };
	int dx[] = { 0,1,0,-1 };
	int arr[N][N] = { 0 }; 
	int n, x = 1, y = 1, m = 0; 
	cin >> n; 
	for (int i = 1; i <= n * n; i++) 
	{
		arr[x][y] = i;
		int a = x + dx[m], b = y + dy[m];
		//越界修改方向向量
		if (a < 1 || a > n || b < 1 || b > n || arr[a][b])
		{
			m = (m + 1) % 4; 
			a = x + dx[m], b = y + dy[m];
		}
		x = a, y = b;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			printf("%3d", arr[i][j]);
		}
		cout << endl;
	}

	return 0;
}