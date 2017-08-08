#include<stack>
#include<iostream>
#include<assert.h>
#include <fstream>
using namespace std;

const int N = 10;
struct Pos
{
	size_t _row; //��
	size_t _col; //��

};

void InitMaze(int maze[][N], size_t N)  //���ļ��ж����Թ�����д�����
{
	FILE* fin = fopen("map.txt","r");
	assert(fin);
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N;)
		{
			int value = getc(fin);
			if (value == '0' || value == '1')
			{
				maze[i][j] = value - '0';
				j++;
			}
			else if (value == EOF)
				cout << "���ʳ���" << endl;
		}
	}

}
void PrintMaze(int maze[][N],size_t N)   //��ӡ�Թ�
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			cout << maze[i][j]<<"  ";
		}
		cout << endl;
	}
	cout << endl;
}

bool CheckAccess(int maze[][N], size_t N, Pos cur,Pos next)  // �ж�λ���Ƿ�Ϸ�������λ���Ƿ�Ϊͨ·
{
	assert(maze);
	if (next._col < 0 || next._col >= N
		|| next._row < 0 || next._row >= N
		|| maze[next._row][next._col] == 1)
	{
		return false;
	}
	if (maze[next._row][next._col] == 0)
	{
		return true;
	}
	return maze[cur._row][cur._col] < maze[next._row][next._col];
}

void GetMazePathR(int maze[][N], size_t N, Pos cur,stack<Pos>& shortPath, stack<Pos>& path)  //������ͨ·
{
	assert(maze);
	path.push(cur);
	if (cur._row == N - 1 || cur._row == 0
		|| cur._col == N-1)
	{
		if (shortPath.empty() || path.size() < shortPath.size())
		{
			shortPath = path;
		}
		path.pop();
		return;
	}
	Pos next;

	//��
	next = cur;
	next._row -= 1;
	if (CheckAccess(maze, N, cur, next))
	{
		maze[next._row][next._col] = maze[cur._row][cur._col] + 1;
		GetMazePathR(maze, N, next, shortPath, path);
		
	}
	
	//��
	next = cur;
	next._row += 1;
	if (CheckAccess(maze, N, cur, next))
	{
		maze[next._row][next._col] = maze[cur._row][cur._col] + 1;
		GetMazePathR(maze, N, next, shortPath, path);
	}
	//��
	next = cur;
	next._col -= 1;
	if (CheckAccess(maze, N, cur, next))
	{
		maze[next._row][next._col] = maze[cur._row][cur._col] + 1;
		GetMazePathR(maze, N, next, shortPath, path);
	}
	//��
	next = cur;
	next._col += 1;
	if (CheckAccess(maze, N, cur, next))
	{
		maze[next._row][next._col] = maze[cur._row][cur._col] + 1;
		GetMazePathR(maze, N, next, shortPath, path);
	}
	path.pop();
}



void PtintRose(stack<Pos>& shortPath)  //��ӡ���ͨ··��
{
	int size = shortPath.size();
	int row[10];
	int col[10];
	for (int i = 0; i < size;i++)
	{
		row[i] = shortPath.top()._row;
		col[i] = shortPath.top()._col;
		shortPath.pop();
	}
	for (int i = size; i > 0; i--)
	{
		cout << "��" << size-i+1 << "��λ��: ";
		cout << "�У�" << row[i-1]<<" ";
		cout << "�У�" << col[i-1];
		cout << endl;
	}
}
void TestMaze()
{
	int maze[N][N];
	InitMaze(maze, N);
	PrintMaze(maze, N);
	Pos cur;
	cur._row = 1;
	cur._col = 0;
	maze[1][0] = 2;
	stack<Pos> shortPath;
	stack<Pos> path;

	
	GetMazePathR(maze, N, cur, shortPath, path);
	PrintMaze(maze, N);
	cout << shortPath.size() << endl;
	PtintRose(shortPath);
}
//
//class Maze
//{
//public:
//	Maze(const int& x, const int& y)
//		:_row(x)
//		, _col(y)
//	{}
//	void GetMazeMap()
//	{
//		FILE* fin = fopen("map.txt", "r");
//			assert(fin);
//			for (size_t i = 0; i < N; i++)
//			{
//				for (size_t j = 0; j < N;)
//				{
//					int value = getc(fin);
//					if (value == '0' || value == '1')
//					{
//						_maze[i][j] = value - '0';
//						j++;
//					}
//					else if (value == EOF)
//						cout << "���ʳ���" << endl;
//				}
//			}
//	}
//	void GetShortPath(Pos cur)
//	{
//		assert(_maze);
//		stack<Pos> _path;
//		_path.push(cur);
//	if (cur._row == N - 1 || cur._row == 0
//		|| cur._col == N-1)
//	{
//		if (_shortPath.empty() || _path.size() < _shortPath.size())
//		{
//			_shortPath = _path;
//		}
//		_path.pop();
//		return;
//	}
//	Pos next;
//
//	//��
//	next = cur;
//	next._row -= 1;
//	if (CheckAccess(cur, next))
//	{
//		_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
//		GetShortPath(next);
//		
//	}
//	
//	//��
//	next = cur;
//	next._row += 1;
//	if (CheckAccess( cur, next))
//	{
//		_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
//		GetShortPath(next);
//	}
//	//��
//	next = cur;
//	next._col -= 1;
//	if (CheckAccess(cur, next))
//	{
//		_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
//		GetShortPath(next);
//	}
//	//��
//	next = cur;
//	next._col += 1;
//	if (CheckAccess( cur, next))
//	{
//		_maze[next._row][next._col] = _maze[cur._row][cur._col] + 1;
//		GetShortPath(next);
//	}
//	_path.pop();
//	}
//
//	void PrintMaze()
//	{
//		for (size_t i = 0; i < N; i++)
//		{
//			for (size_t j = 0; j < N; j++)
//			{
//				cout << _maze[i][j] << "  ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//	}
//	bool CheckAccess(Pos cur, Pos next)
//	{
//		assert(_maze);
//		if (next._col < 0 || next._col >= N
//			|| next._row < 0 || next._row >= N
//			|| _maze[next._row][next._col] == 1)
//		{
//			return false;
//		}
//		if (_maze[next._row][next._col] == 0)
//		{
//			return true;
//		}
//		return _maze[cur._row][cur._col] < _maze[next._row][next._col];
//	}
//protected:
//	int **_maze;
//	int _row;
//	int _col;
//	stack<Pos> _shortPath;
//};
//void Text()
//{
//	Maze maze(1,0);
//	Pos cur;
//	cur._col = 0;
//	cur._row = 1;
//	maze.GetMazeMap();
//	maze.PrintMaze();
//	maze.GetShortPath(cur);
//	maze.PrintMaze();
//}