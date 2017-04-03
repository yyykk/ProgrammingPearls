// demo.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdio.h>
#include "iostream"
#include "fstream"
#include "vector"
#include "list"
using namespace std;

int NodeNum, LinkNum, CostNum, ServeCost;
//�Զ�λ������ʽ�洢��ͼ������ÿ����·������ֵ��
//�������ڲ�Ҳ��һ�����飬��һ��ֵΪ�����ڶ���Ϊ��λ���÷�
//�������ڵ�֮�䲻��������ֵȫΪ0��intĬ��ֵ
vector<vector<vector<int>>> Net;
//�����ѽڵ㵥����ţ��ڲ�����������ֵ����һ��Ϊ��������ڵ�ID���ڶ���Ϊ��Ƶ��������
vector<vector<int>> CostNode;
//������Ľڵ㣬�ڲ������һ��ֵΪ����ڵ�ID���ڶ���ֵΪ���������
vector<vector<int>> NeedHandle;
//��ǰȷ���ķ��������ڲ������һ��ֵΪ����ڵ�ID���ڶ���ֵΪ���������أ�������ֵΪ1��÷������ڱ��ε������ֱ�ʹ����
vector<vector<int>> Server;
//ÿ��·���Ļ���
vector<int> RoadCost;
//ÿ��ʹ��ǰ������丳ֵ��ȫ��ʹ�õ��м����
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

	//����n*n����
	for (int i = 0; i < NodeNum; ++i) {
		vector<vector<int>> Node(NodeNum, {0, 0});
		Net.push_back(Node);
	}

	//��������ĳһ������ֵ�������ڵ�����������һ��ֵΪ�����ڶ���ֵΪ��λ���÷�
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

//v�е�һ��Ԫ���Ƿ����ֵΪp��Ԫ��
int FindFirst(int p, vector<vector<int>> &v) {
	for (int i = 0; i < v.size(); ++i) {
		if (v[i][0] == p) {
			return i;
		}
	}
	return -1;
}

//��Net��ĳһ��Ԫ����Ѱ����С��Ԫ�أ�0���⣩
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

//v1ʹ��v2�Ĵ���,��v2�����㹻�򷵻�v1��ֵ���򷵻ش����ֵ
int ReduceB(int &v1, vector<int> &v2) {
	int temp = 0;
	if (v1 >= v2[0]) {//v2������
		v1 -= v2[0];
		temp = v2[0];
		v2[0] = 0;
		return temp;
	}else {//v2�����㹻
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
			if ((temp = FindFirst(ThisID, Server)) != -1 && Server[temp][2] == 1) continue;//�õ����������ڵ���
			if ((temp = FindFirst(ThisID, Server)) != -1) Server.erase(Server.begin() + temp);
			
			for (int j = 0; j < NodeNum && ThisStream > 0; ++j) {//�ڽӽڵ��Ƿ��з�����
				if (Net[ThisID][j][0] && (temp = FindFirst(j, Server)) != -1) {//�ڵ�j�з�������������ΪServer������ĵ�temp - 1��Ԫ��
					visited[j] = 1;
					Server[temp][2] = 1;//���ε����÷��������ܱ�ɾ��
					Server[temp][1] += ReduceB(ThisStream, Net[ThisID][j]);
				}
			}
			//ShowLog(visited);
			for (int j = 0; j < NodeNum && ThisStream > 0; ++j) {//Ѱ��̽���Ľڵ�
				if (visited[j] == 1) continue;
				if (Net[ThisID][j][0] && (temp = FindFirst(j, NeedHandle)) != -1) {//��Χ�Ľڵ��д��ڴ�����Ľڵ�j,�Ҹýڵ�û�з���������FindFirst�еĵ�temp-1λ��
					visited[j] = 1;
					Server.push_back({ j, ReduceB(ThisStream, Net[ThisID][j]) });//����������
				}
			}
			//ShowLog(visited);
			while (ThisStream > 0) {//�ڵ�����̽����̽��λ���������κζ���
				temp = FindMin(Net[ThisID], visited);
				visited[temp] = 1;
				NeedHandle.push_back({ temp, ReduceB(ThisStream, Net[ThisID][temp]) });
			}
		}
		ShowLog();
}

void simple() {//������ȫ���������ѽڵ���
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