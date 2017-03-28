// demo.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include "iostream"
#include "fstream"
#include "vector"
#include "list"
using namespace std;

int NodeNum, LinkNum, CostNum, ServeCost;
//以二位数组形式存储地图，由于每条链路有两个值，所以最内层也是一个数组，第一个值为带宽，第二个为单位租用费
//若两个节点之间不相连，则值全为0，int默认值
vector<vector<vector<int>>> Net;
//将消费节点单独存放，内部数组有两个值，第一个为相连网络节点ID，第二个为视频带宽消耗
vector<vector<int>> CostNode;
//待处理的节点，内部数组第一个值为网络节点ID，第二个值为待处理带宽
vector<vector<int>> NeedHandle;
//当前确定的服务器，内部数组第一个值为网络节点ID，第二个值为服务器负载
vector<vector<int>> Server;

int temp;

void InitNet() {
	ifstream infile;
	infile.open("./case_example/case4.txt", ios::in);
	if (!infile) {
		cout << "error open" << endl;
		return;
	}
	//int blank;//处理输入的空行
	infile >> NodeNum >> LinkNum >> CostNum;
	infile >> ServeCost;

	//构建n*n矩阵
	for (int i = 0; i < NodeNum; ++i) {
		vector<vector<int>> Node(NodeNum);
		Net.push_back(Node);
	}

	//若矩阵中某一坐标有值（两个节点相连），第一个值为带宽，第二个值为单位租用费
	int LinkBegin, LinkEnd, BandWidth, PerCost;
	for (int i = 0; i < LinkNum; ++i) {
		infile >> LinkBegin >> LinkEnd >> BandWidth >> PerCost;
		Net[LinkBegin][LinkEnd].push_back(BandWidth);
		Net[LinkBegin][LinkEnd].push_back(PerCost);
		Net[LinkEnd][LinkBegin].push_back(BandWidth);
		Net[LinkEnd][LinkBegin].push_back(PerCost);
	}

	int NodeID, BandCost;
	for (int i = 0; i < CostNum; ++i) {
		infile >> NodeID >> BandCost;
		vector<int> Cost{ NodeID, BandCost };
		CostNode.push_back(Cost);
	}
	infile.close();
}

int FindFirst(int p, vector<vector<int>> &v) {//是否存在值为p的元素
	for (int i = 0; i < v.size(); ++i) {
		if (v[i][0] == p) {
			return i;
		}
	}
	return -1;
}

int FindMin(vector<vector<int>> &v, int* visited) {
	int Min = 0, j = 0;
	for (int i = 0; i < v.size(); ++i) {
		if (visited[i] != 0) {
			continue;
		}else if (Min = 0) {
			Min = v[i][1];
			j = i;
		}else if (v[i][1] < Min) {
			Min = v[i][1];
			j = i;
		}
	}
	return j;
}

int ReduceB(vector<int> &v1, vector<int> &v2) {
	if (v1[1] >= v2[0]) {
		v1[1] -= v2[0];
		Server[temp][1] += v2[0];
		v2[0] = 0;
		return 1;
	}else {
		v1[1] = 0;
		v2[0] -= v1[1];
		return -1;
	}
}

void type1() {
	for (int i = 0; i < CostNode.size(); ++i) {
		NeedHandle.push_back(CostNode[i]);
		Server.push_back(CostNode[i]);
	}
	while (NeedHandle.size() != 0) {
		int SizeTemp = NeedHandle.size();
		for (int i = 0; i < SizeTemp; ++i) {
			int MinCost = 0;
			int MinCostID = 0;
			int *visited = new int[NodeNum];
			for (int j = 0; j < NodeNum; ++j) {
				if ((temp = FindFirst(j, Server)) != -1) {
					visited[j] = 1;
					Server[temp][1] += NeedHandle[i][1];
					if (ReduceB(NeedHandle[i], Net[NeedHandle[i][0]][j]))
						break;
				}
			}
			while (NeedHandle[i][1] > 0) {
				temp = FindMin(Net[NeedHandle[i][0]], visited);
				visited[temp] = 1;
				ReduceB(NeedHandle[i], Net[NeedHandle[i][0]][temp]);
			}
			delete visited;
		}
		NeedHandle.erase(NeedHandle.begin(), NeedHandle.begin() + SizeTemp - 1);
	}
}

void simple() {//服务器全放置于消费节点上
	ofstream outfile;
	outfile.open("result.txt", ios::out);
	outfile << CostNum << endl;
	cout << CostNum << endl;
	outfile << endl;
	cout << endl;
	for (int i = 0; i < CostNum; ++i) {
		outfile << CostNode[i][0] << " " << i << " " << CostNode[i][1] << endl;
		cout << CostNode[i][0] << " " << i << " " << CostNode[i][1] << endl;
	}
	outfile.close();
}

int main() {
	InitNet();
	//simple();

	system("pause");
}