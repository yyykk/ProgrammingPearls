// demo.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdio.h>
#include "iostream"
#include "fstream"
#include "vector"
#include "list"
using namespace std;

int NodeNum, LinkNum, CostNum, ServeCost;
//�Զ�λ������ʽ�洢��ͼ������ÿ����·������ֵ���������ڲ�Ҳ��һ�����飬��һ��ֵΪ�����ڶ���Ϊ��λ���÷�
//�������ڵ�֮�䲻��������ֵȫΪ0��intĬ��ֵ
vector<vector<vector<int>>> Net;
//�����ѽڵ㵥����ţ��ڲ�����������ֵ����һ��Ϊ��������ڵ�ID���ڶ���Ϊ��Ƶ��������
vector<vector<int>> CostNode;
//������Ľڵ㣬�ڲ������һ��ֵΪ����ڵ�ID���ڶ���ֵΪ���������
vector<vector<int>> NeedHandle;
//��ǰȷ���ķ��������ڲ������һ��ֵΪ����ڵ�ID���ڶ���ֵΪ����������
vector<vector<int>> Server;

int temp;

void InitNet() {
	ifstream infile;
	infile.open("./case_example/case4.txt", ios::in);
	if (!infile) {
		cout << "error open" << endl;
		return;
	}
	//int blank;//��������Ŀ���
	infile >> NodeNum >> LinkNum >> CostNum;
	infile >> ServeCost;

	//����n*n����
	for (int i = 0; i < NodeNum; ++i) {
		vector<vector<int>> Node(NodeNum);
		Net.push_back(Node);
	}

	//��������ĳһ������ֵ�������ڵ�����������һ��ֵΪ�����ڶ���ֵΪ��λ���÷�
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

int FindFirst(int p, vector<vector<int>> &v) {//�Ƿ����ֵΪp��Ԫ��
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
	//simple();

	system("pause");
}