#include "deploy.h"
#include <stdio.h>
#include "iostream"
#include "fstream"
#include "vector"
using namespace std;

int NodeNum, LinkNum, CostNum, ServeCost;
//以二位数组形式存储地图，由于每条链路有两个值，所以最内层也是一个数组，第一个值为带宽，第二个为单位租用费
//若两个节点之间不相连，则值全为0，int默认值
vector<vector<vector<int>>> Net;
//将消费节点单独存放，内部数组有两个值，第一个为相连网络节点ID，第二个为视频带宽消耗
vector<vector<int>> CostNode;

void InitNet(char * topo[MAX_EDGE_NUM]){
	int blank;//处理输入的空行
	sscanf(topo[0], "%d, %d, %d", &NodeNum, &LinkNum, &CostNum);
	sscanf(topo[1], "%d", &ServeCost);
	
	//构建n*n矩阵
	for (int i = 0; i < NodeNum; ++i){
		vector<int> Node(NodeNum);
		Net.push_back(Node);
	}
	
	//若矩阵中某一坐标有值（两个节点相连），第一个值为带宽，第二个值为单位租用费
	int LinkBegin, LinkEnd, BandWidth, PerCost;
	for(int i = 0; i < LinkNum; ++i){
		sscanf(topo[i + 2], "%d, %d, %d, %d", &LinkBegin, &LinkEnd, &BandWidth, &PerCost);
		Net[LinkBegin][LinkEnd].push_back(BandWidth);
		Net[LinkBegin][LinkEnd].push_back(PerCost);
	}
	
	int NodeID, BandCost;
	for (int i = 0; i < CostNum; ++i){
		sscanf(topo[i + LinkNum], "%d, %d", &NodeID, &BandCost);
		vector<int> Cost{NodeID, BandCost};
		CostNode.push_back(Cost);
	}
}

char* simple(){//服务器全放置于消费节点上
	char *result;
	InitNet();
	sprintf(*result, "%d\n\n", CostNum);
	for (int i = 0; i < CostNum; ++i){
		sprintf(*result, "%d %d %d\n", CostNum[i][0], i, CostNode[i][1]);
	}
	return simple;
}

//你要完成的功能总入口
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{

	InitNet(topo);
	char * topo_file = simple();
	//char * topo_file = (char *)"17\n\n0 8 0 20\n21 8 0 20\n9 11 1 13\n21 22 2 20\n23 22 2 8\n1 3 3 11\n24 3 3 17\n27 3 3 26\n24 3 3 10\n18 17 4 11\n1 19 5 26\n1 16 6 15\n15 13 7 13\n4 5 8 18\n2 25 9 15\n0 7 10 10\n23 24 11 23";

	// 直接调用输出文件的方法输出到指定文件中(ps请注意格式的正确性，如果有解，第一行只有一个数据；第二行为空；第三行开始才是具体的数据，数据之间用一个空格分隔开)
	write_result(topo_file, filename);

}
