// demo.cpp : 定义控制台应用程序的入口点。
//
#include "vector"
#include "iostream"
#include "numeric"
#include "algorithm"
#include "math.h"
#include "time.h"
#include "windows.h"
using namespace std;

 
int main() {
	int MinSize = 1;
	int MaxSize = 1000;
	int FishNum = 4;
	int result = 0;
	vector<int> FishSize({2, 8, 64, 1000});
	vector<int> Size(MaxSize - MinSize + 2, 0);
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	int ans = 0;
	for (int size = MinSize; size <= MaxSize; size++) {
		bool ok = true;
		for (int i = 0; i < FishNum; i++) {
			if (!((size < 2 * FishSize[i] || size > 10 * FishSize[i]) && (FishSize[i] < 2 * size || FishSize[i] > 10 * size))) {
				ok = false;
				break;
			}
		}

		if (ok) {
			cout << size << "\t";
			ans++;
		}	
	}
	cout << endl;
	cout << "ans = " << ans << endl;
	QueryPerformanceCounter(&t2);
	cout << (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart << endl;

	LARGE_INTEGER t11, t22, tcc;
	QueryPerformanceFrequency(&tcc);
	QueryPerformanceCounter(&t11);
	for (int i = 0; i < FishNum; ++i) {
		for (int j = ceil(FishSize[i] / 10); j <= FishSize[i] / 2; ++j) {
			Size[j] = 1;
		}
		for (int j = FishSize[i] * 2; j <= FishSize[i] * 10; ++j) {
			if (j < Size.size()) {
				Size[j] = 1;
			}
		}
	}
	for (int i = 0; i < FishNum; ++i) {
		Size[FishSize[i]] = 0;
	}
	for (int i = 1; i < Size.size(); ++i) {
		if (Size[i] == 1) {
			continue;
		}else {
			cout << i << "\t";
			++result;
		}
	}
	cout << endl;
	cout <<"result = "<< result << endl;
	QueryPerformanceCounter(&t22);
	cout << (t22.QuadPart - t11.QuadPart)*1.0 / tcc.QuadPart << endl;
	system("pause");
	return 0;
}