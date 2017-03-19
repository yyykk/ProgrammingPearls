/*

在一个N*N的数组中寻找所有横，竖，左上到右下，右上到左下，四种方向的直线连续D个数字的和里面最大的值 
输入描述:
每个测试输入包含1个测试用例，第一行包括两个整数 N 和 D :
3 <= N <= 100
1 <= D <= N
接下来有N行，每行N个数字d:
0 <= d <= 100


输出描述:
输出一个整数，表示找到的和的最大值

输入例子:
4 2
87 98 79 61
10 27 95 70
20 64 73 29
71 65 15 0

输出例子:
193

*/



#include "vector"
#include "iostream"
#include "numeric"
#include "algorithm"
#include "math.h"
#include "time.h"
#include "windows.h"
#include "string"
#include "queue"
using namespace std;
int row(vector<vector<int>> &v, int D) {
	int max = 0;
	for (int i = 0; i < v.size(); ++i) {
		queue<int> q;
		int temp = 0;
		for (int j = 0; j < v.size(); ++j) {
			q.push(v[i][j]);
			temp += v[i][j];
			if (q.size() == D) {
				if (max < temp) {
					max = temp;
				}
				temp -= q.front();
				q.pop();
			}
		}
	}
	//cout << "RowMax = " << max << endl;
	return max;
}

int col(vector<vector<int>> &v, int D) {
	int max = 0;
	for (int i = 0; i < v.size(); ++i) {
		queue<int> q;
		int temp = 0;
		for (int j = 0; j < v.size(); ++j) {
			q.push(v[j][i]);
			temp += v[j][i];
			if (q.size() == D) {
				if (max < temp) {
					max = temp;
				}
				temp -= q.front();
				q.pop();
			}
		}
	}
	//cout << "ColMax = " << max << endl;
	return max;
}

int LeftDown(vector<vector<int>> &v, int D) {
	int max = 0;
	for (int i = 0; i < v.size(); ++i) {
		queue<int> q;
		int temp = 0;
		for (int j = 0; j < i + 1; ++j) {
			q.push(v[v.size() - i + j - 1][j]);
			temp += v[v.size() - i + j - 1][j];
			if (q.size() == D) {
				if (max < temp) {
					max = temp;
				}
				temp -= q.front();
				q.pop();
			}
		}
	}
	for (int i = v.size() - 1; i > 0; --i) {
		queue<int> q;
		int temp = 0;
		for (int j = 0; j < i; ++j) {
			q.push(v[j][v.size() - i + j]);
			temp += v[j][v.size() - i + j];
			if (q.size() == D) {
				if (max < temp) {
					max = temp;
				}
				temp -= q.front();
				q.pop();
			}
		}
	}
	//cout << "LeftDownMax = " << max << endl;
	return max;
}

int RightDown(vector<vector<int>> &v, int D) {
	int max = 0;
	for (int i = 0; i < v.size(); ++i) {
		queue<int> q;
		int temp = 0;
		for (int j = 0; j < i + 1; ++j) {
			q.push(v[j][i - j]);
			temp += v[j][i - j];
			if (q.size() == D) {
				if (max < temp) {
					max = temp;
				}
				temp -= q.front();
				q.pop();
			}
		}
	}
	for (int i = v.size() - 1; i > 0; --i) {
		queue<int> q;
		int temp = 0;
		for (int j = 0; j < i; ++j) {
			q.push(v[v.size() - i][v.size() - j - 1]);
			temp += v[v.size() - i][v.size() - j - 1];
			if (q.size() == D) {
				if (max < temp) {
					max = temp;
				}
				temp -= q.front();
				q.pop();
			}
		}
	}
	//cout << "RightDownMax = " << max << endl;
	return max;
}

int main() {
	int result = 0;
	int N, D;
	int temp;
	cin >> N >> D;
	vector<vector<int>> matrix;
	for (int i = 0; i < N; ++i) {
		vector<int> vtemp;
		for (int j = 0; j < N; ++j) {
			cin >> temp;
			vtemp.push_back(temp);
		}
		matrix.push_back(vtemp);
	}
	row(matrix, D);
	col(matrix, D);
	LeftDown(matrix, D);
	RightDown(matrix, D);
	int temp1 = max(row(matrix, D), col(matrix, D));
	int temp2 = max(LeftDown(matrix, D), RightDown(matrix, D));
	result = max(temp1, temp2);
	cout << result << endl; 
	system("pause");
	return 0;
}