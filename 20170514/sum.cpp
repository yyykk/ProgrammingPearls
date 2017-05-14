/*

题目描述
输入n， 求y1=1!+3!+...m!(m是小于等于n的最大奇数） y2=2!+4!+...p!(p是小于等于n的最大偶数)。 
输入描述:
每组输入包括1个整数：n


输出描述:
可能有多组测试数据，对于每组数据，
输出题目要求的y1和y2

输入例子:
4

输出例子:
7 26

*/

#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

int demo(int n){
    if(n == 1){
        return n;
    }else{
        return n * demo(n - 1);
    }
}


int main(){
    int n;
	while (cin >> n) {
		int y1 = 0, y2 = 0;
        for(int i = 1; i <= n; ++i){
            if(i % 2 == 0){
                y2 += demo(i);
            }else{
                y1 += demo(i);
            }
        }
        cout<< y1 << " " << y2 << endl;
	}
    return 0;
}