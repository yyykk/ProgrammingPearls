// Learn.cpp : 定义控制台应用程序的入口点。
//
/*
#pragma comment(lib, "MSIMG32.LIB")
#include "stdio.h"
#include "string.h"

#include "cstring"
#include "graphics.h"

#include "vector"
#include "time.h"
#include "conio.h"
#include "stdlib.h"
#include "math.h"
*/

/*

using namespace std;

#define MaxWeight 600
#define MaxHigh 400
#define TankWeight 50
#define TankHigh 50
#define PlaneWeight 50
#define PlaneHigh 50
#define FireWeight 50
#define FireHigh 350
#define MaxTime 7

IMAGE pic, doctor, fire, boom, tank, plane;
HDC PicHDC;

struct Boom {
	int time;
	int x;
	int y;
	HDC imghdc;
	int maskcolor;
};

vector<Boom> vboom;

Boom InitBoom(int x, int y) {
	DWORD *pmask;
	Boom NewBoom;
	NewBoom.time = 7 * 4;
	NewBoom.x = x;
	NewBoom.y = y;
	NewBoom.imghdc = GetImageHDC(&boom);
	pmask = GetImageBuffer(&boom);
	NewBoom.maskcolor = BGR(pmask[0]);
	return NewBoom;
}

void TranImage(struct Boom *boom) {
	TransparentBlt(PicHDC, boom->x, boom->y,
		PlaneWeight, PlaneHigh, boom->imghdc, 
		0, 0, 
		PlaneWeight, PlaneHigh, boom->maskcolor);
}

void FireBoom() {
	for (int i = 0; i < vboom.size(); ++i) {
		if (vboom[i].time > 0) {
			vboom[i].time -= 1;
			vboom[i].y -= TankHigh / 4;
			TranImage(&vboom[i]);
		}
	}
}

struct Plane {
	int time;
	int x;
	int y;
	HDC imghdc;
	int maskcolor;
};

vector<Plane> vplane;

Plane InitPlane(int x, int y) {
	DWORD *pmask;
	Plane SlefPlane;
	SlefPlane.time = 12 * 4;
	SlefPlane.x = x;
	SlefPlane.y = y;
	SlefPlane.imghdc = GetImageHDC(&plane);
	pmask = GetImageBuffer(&plane);
	SlefPlane.maskcolor = BGR(pmask[0]);
	return SlefPlane;
}

void TranImage(struct Plane *plane) {
	TransparentBlt(PicHDC, plane->x, plane->y,
		PlaneWeight, PlaneHigh, plane->imghdc,
		0, 0,
		PlaneWeight, PlaneHigh, plane->maskcolor);
}

void FirePlane() {
	for (int i = 0; i < vplane.size(); ++i) {
		if (vplane[i].time > 0) {
			vplane[i].time -= 1;
			vplane[i].x -= PlaneHigh / 4;
			TranImage(&vplane[i]);
		}
	}
}

struct Tank {
	int x;
	int y;
	HDC imghdc;
	int maskcolor;
};

void InitTank(Tank *SlefTank,int x, int y) {
	DWORD *pmask;
	SlefTank->x = x;
	SlefTank->y = y;
	SlefTank->imghdc = GetImageHDC(&tank);
	pmask = GetImageBuffer(&tank);
	SlefTank->maskcolor = BGR(pmask[0]);
}

void TranImage(struct Tank *tank) {
	TransparentBlt(PicHDC, tank->x, tank->y,
		PlaneWeight, PlaneHigh, tank->imghdc,
		0, 0,
		PlaneWeight, PlaneHigh, tank->maskcolor);
}

int GetKeyValue() {
	int KeyValue;
	KeyValue = _getwch();
	return KeyValue;
}

void Destory() {
	int i = 0, j = 0;
	for (; i < vplane.size(); ++i) {
 		if (vplane[i].time == 0) continue;
 		for (; j < vboom.size(); ++j) {
			if (vboom[j].time == 0) continue;
			if ((abs(vplane[i].x - vboom[j].x) <= PlaneHigh) && (abs(vplane[i].y - vboom[j].y) <= PlaneWeight)) {
				vplane[i].time = 0;
				vboom[j].time = 0;
				putimage(vplane[i].x, vplane[i].y, &doctor);
			}
		}
	}
}

int GetD() {//上0下1左2右3空格4
	int D = 0, value = 0;
	value = GetKeyValue();
	if (value == 32) {
		D = 4;
	}else if (value == 224) {
		switch (GetKeyValue()) {
			case 72: D = 0; break;
			case 80: D = 1; break;
			case 75: D = 2; break;
			case 77: D = 3; break;
		}
	}
	return D;
}

void InitImage() {
	loadimage(&boom, _T("./source/Boom.bmp"), TankWeight, TankHigh);

	loadimage(&pic, _T("./walle.jpg"), MaxWeight, MaxHigh);

	loadimage(&tank, _T("./source/Tank.bmp"), TankWeight, TankHigh);

	loadimage(&doctor, _T("./source/doctor.jpg"), TankWeight, TankHigh);

	loadimage(&fire, _T("./source/Boom.jpg"), FireWeight, FireHigh);

	loadimage(&plane, _T("./source/Plane.bmp"), TankWeight, TankHigh);
}

int main() {
	int x = MaxWeight / 2, y = MaxHigh - 50;
	
	long int TankStart = clock(), PlaneStart = clock();

	Tank selfTank;
	
	srand((unsigned)time(NULL));

	initgraph(MaxWeight, MaxHigh);

	InitImage();

	while (1) {
		loadimage(&pic, _T("./walle.jpg"), MaxWeight, MaxHigh);
		PicHDC = GetImageHDC(&pic);
		InitTank(&selfTank, x, y);
		TranImage(&selfTank);
		if (_kbhit()) {
			switch (GetD()) {
			case 4: vboom.push_back(InitBoom(x, y)); break;
			case 2: x -= 20; break;
			case 3: x += 20; break;
			default: break;
			}
		}
		if (clock() - PlaneStart >= 100) {
			if (clock() % 7 == 0) {
				vplane.push_back(InitPlane(MaxWeight, rand() % 201));
			}
			PlaneStart = clock();
		}
		if (clock() - TankStart >= 50) {
			FirePlane();
			FireBoom();
			SetWorkingImage();
			putimage(0, 0, &pic);
			TankStart = clock();
		}
		Destory();
	}
	
	system("pause");
	return 0;
}*/
/*
class TreeNode {
public:
	void setData(char data) {
		data = data;
	}
	TreeNode(char data) {
		data = data;
		leftChild = nullptr;
		rightChild = nullptr;
	}
	TreeNode() {};
private:
	char data;
	TreeNode *leftChild;
	TreeNode *rightChild;
};
*/

#include "iostream"
#include "string"
#include "stack"
using namespace std;
class Tree {
public:
	Tree(char d) {
		leftChild = nullptr;
		rightChild = nullptr;
		data = d;
		tag = 0;
	}
	Tree() {
		leftChild = nullptr;
		rightChild = nullptr;
		tag = 0;//后序遍历标志位
	}
	void initTree(char* &str, Tree* &t);//使用字符串初始化二叉树，#表示空节点
	void fVisit();//先序遍历
	void mVisit();//中序遍历
	void bVisit();//后序遍历
	
private:
	Tree *leftChild;
	Tree *rightChild;
	char data;
	int tag;
};

void Tree::initTree(char* &str, Tree* &t){//先序构建二叉树
	if (*str != '#') {
		t = new Tree(*str);
		initTree(++str, t->leftChild);
		initTree(++str, t->rightChild);
	}
}

void Tree:: fVisit(){
	stack<Tree *> s;
	Tree *t = this;
	while (t != nullptr || !s.empty()) {
		if (t != nullptr) {
			cout << t->data << "\t";
			if (t->rightChild != nullptr) {
				s.push(t->rightChild);
			}
			t = t->leftChild;
		}else{
			t = s.top();
			s.pop();
		}
	}
}

void Tree::mVisit(){
	stack<Tree *> s;
	Tree *t = this;
	while (t != nullptr || !s.empty()) {
		if (t != nullptr) {
			s.push(t);
			t = t->leftChild;
		}else {
			cout << s.top()->data << "\t";
			t = s.top()->rightChild;
			s.pop();
		}
	}
}

void Tree::bVisit(){
	stack<Tree *> s;
	Tree *t = this;
	while (t != nullptr || !s.empty()) {
		if (t != nullptr) {
			s.push(t);
			t = t->leftChild;
		}else {
			if (s.top()->tag == 0) {
				t = s.top()->rightChild;
				s.top()->tag = 1;
			}else {
				cout << s.top()->data << "\t";
				s.pop();
			}
		}
	}
}

int main() {
	Tree *t = new Tree;
	char *str = "1378###6##59###";
	t->initTree(str, t);
	cout << "先序遍历" << endl;
	t->fVisit();
	cout << endl;
	cout << "中序遍历" << endl;
	t->mVisit();
	cout << endl;
	cout << "后序遍历" << endl;
	t->bVisit();
	cout << endl;
	system("pause");
	return 0;
}

