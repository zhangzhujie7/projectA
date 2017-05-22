#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
int row, col = 0;
vector<vector<int>> maze;
vector<vector<int>> replica;
vector<vector<int>> result;
int min = 1000;
int nx[4][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };
void dfs(int x, int y, int step)
{
	if (x == row-1&&y == col-1)
	{
		if (step < min)
		{
			min = step;
			result = replica;
		}
		return;
	}
	for (int k = 0; k <= 3; k++)
	{
		int tx = x + nx[k][0];
		int ty = y + nx[k][1];
		if (tx<0 || tx>row-1 || ty<0 || ty>col -1)
			continue;
		if (maze[tx][ty] == 0 && replica[tx][ty] == 0)
		{
			replica[tx][ty] = 2;
			dfs(tx, ty, step + 1);
			replica[tx][ty] = 0;
		}
	}
	return;
}

int main()
{
	string fileName = "mg1.txt";
	string buffer;
	ifstream fs(fileName, ios::in);

	vector<int> oneRow;

	if (fs.is_open())
	{
		stringstream ss;
		getline(fs, buffer);
		ss.str(buffer);
		ss >> row >> col ;
		ss.clear();
		int tmp;
		while (!fs.eof())
		{
			getline(fs, buffer);
			ss.str(buffer);
			for (int i = 0; i < col; i++)
			{
				ss >> tmp;
				oneRow.push_back(tmp);
			}
			maze.push_back(oneRow);
			oneRow.clear();
			ss.clear();
		}
	}
	fs.close();
	replica = maze;

	dfs(0, 0, 0);
	result[0][0] = 2;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}