// demo.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include "iostream"
#include "fstream"
#include "vector"
#include "list"
using namespace std;

int NodeNum, LinkNum, CostNum, ServeCost;
//以二位数组形式存储地图，由于每条链路有两个值，
//所以最内层也是一个数组，第一个值为带宽，第二个为单位租用费
//若两个节点之间不相连，则值全为0，int默认值
vector<vector<vector<int>>> Net;
//将消费节点单独存放，内部数组有两个值，第一个为相连网络节点ID，第二个为视频带宽消耗
vector<vector<int>> CostNode;
//待处理的节点，内部数组第一个值为网络节点ID，第二个值为待处理带宽
vector<vector<int>> NeedHandle;
//当前确定的服务器，内部数组第一个值为网络节点ID，第二个值为服务器负载，第三个值为1则该服务器在本次迭代中又被使用了
vector<vector<int>> Server;
//每条路径的花费
vector<int> RoadCost;
//每次使用前必须对其赋值，全局使用的中间变量
int temp;

void InitNet() {
	ifstream infile;
	infile.open("./case_example/ykcase.txt", ios::in);
	if (!infile) {
		cout << "error open" << endl;
		return;
	}
	infile >> NodeNum >> LinkNum >> CostNum;
	infile >> ServeCost;

	//构建n*n矩阵
	for (int i = 0; i < NodeNum; ++i) {
		vector<vector<int>> Node(NodeNum, {0, 0});
		Net.push_back(Node);
	}

	//若矩阵中某一坐标有值（两个节点相连），第一个值为带宽，第二个值为单位租用费
	int LinkBegin, LinkEnd, BandWidth, PerCost;
	for (int i = 0; i < LinkNum; ++i) {
		infile >> LinkBegin >> LinkEnd >> BandWidth >> PerCost;
		Net[LinkBegin][LinkEnd][0] = (BandWidth);
		Net[LinkBegin][LinkEnd][1] = (PerCost);
		Net[LinkEnd][LinkBegin][0] = (BandWidth);
		Net[LinkEnd][LinkBegin][1] = (PerCost);
	}

	int CostID, NodeID, BandCost;
	for (int i = 0; i < CostNum; ++i) {
		infile >> CostID >> NodeID >> BandCost;
		CostNode.push_back({ NodeID, BandCost });
	}
	infile.close();
}

//v中第一个元素是否存在值为p的元素
int FindFirst(int p, vector<vector<int>> &v) {
	for (int i = 0; i < v.size(); ++i) {
		if (v[i][0] == p) {
			return i;
		}
	}
	return -1;
}

//在Net中某一行元素中寻找最小的元素（0以外）
int FindMin(vector<vector<int>> &v, vector<int>& visited) {
	int Min = 0, j = 0;
	for (int i = 0; i < v.size(); ++i) {
		if (visited[i] != 0 || v[i][1] == 0) {
			continue;
		}else if (Min == 0) {
			Min = v[i][1];
			j = i;
		}else if (v[i][1] < Min) {
			Min = v[i][1];
			j = i;
		}
	}
	return j;
}

//v1使用v2的带宽,若v2带宽足够则返回v1的值否则返回带宽的值
int ReduceB(int &v1, vector<int> &v2) {
	int temp = 0;
	if (v1 >= v2[0]) {//v2带宽不够
		v1 -= v2[0];
		temp = v2[0];
		v2[0] = 0;
		return temp;
	}else {//v2带宽足够
		v2[0] -= v1;
		temp = v1;
		v1 = 0;
		return temp;
	}
}

void ShowLog() {
	cout << "NeedHandle" << endl;
	for (auto &v : NeedHandle) {
		cout << v[0] << "," << v[1] << "\t";
	}
	cout << endl;
	cout << "Server" << endl;
	for (auto &v : Server) {
		cout << v[0] << "," << v[1] << "," << v[2] << "\t";
	}
	cout << endl;
	cout << "Road" << endl;
	for (auto &mr : Road) {
		for (auto &sr : mr) {
			for (auto &lr : sr) {
				cout << lr << ",";
			}
			cout << endl;
		}
	}
	cout << endl;
	/*cout << "Net" << endl;
	for (auto &v : Net) {
		for (auto &v1 : v) {
			cout << v1[0] << "," << v1[1] << "\t";
		}
		cout << endl;
	}*/
}

void type1() {
	for (int i = 0; i < CostNode.size(); ++i) {
		NeedHandle.push_back({ CostNode[i][0] });
		RoadCost.push_back(CostNode[i][1]);
		Server.push_back({ CostNode[i][0], CostNode[i][1], 0 });
	}

	while (NeedHandle.size() != 0) {
			int ThisID = NeedHandle[0][0], ThisStream = NeedHandle[0][1];
			cout << "Now ID = " << ThisID << endl;
			NeedHandle.erase(NeedHandle.begin());
			if ((temp = FindFirst(ThisID, Server)) != -1 && Server[temp][2] == 1) continue;//该点已与其他节点结合
			if ((temp = FindFirst(ThisID, Server)) != -1) Server.erase(Server.begin() + temp);
			
			for (int j = 0; j < NodeNum && ThisStream > 0; ++j) {//邻接节点是否有服务器
				if (Net[ThisID][j][0] && (temp = FindFirst(j, Server)) != -1) {//节点j有服务器，服务器为Server数组里的第temp - 1个元素
					visited[j] = 1;
					Server[temp][2] = 1;//本次迭代该服务器不能被删除
					Server[temp][1] += ReduceB(ThisStream, Net[ThisID][j]);
				}
			}
			//ShowLog(visited);
			for (int j = 0; j < NodeNum && ThisStream > 0; ++j) {//寻找探出的节点
				if (visited[j] == 1) continue;
				if (Net[ThisID][j][0] && (temp = FindFirst(j, NeedHandle)) != -1) {//周围的节点中存在待处理的节点j,且该节点没有服务器存在FindFirst中的第temp-1位置
					visited[j] = 1;
					Server.push_back({ j, ReduceB(ThisStream, Net[ThisID][j]) });//新增服务器
				}
			}
			//ShowLog(visited);
			while (ThisStream > 0) {//节点往外探出，探出位置无其他任何东东
				temp = FindMin(Net[ThisID], visited);
				visited[temp] = 1;
				NeedHandle.push_back({ temp, ReduceB(ThisStream, Net[ThisID][temp]) });
			}
		}
		ShowLog();
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
	type1();
	//simple();

	system("pause");
}