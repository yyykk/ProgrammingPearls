#include "iostream"
#include "string"
using namespace std;

int result[4][3] = { 0, 5, 0, 0, 4, 0, 1, 6, 2, 0, 3, 0 };
void CoutResult() {
	cout << result[2][0] << result[2][2] << result[3][1] << result[1][1] << result[0][1] << result[2][1] << endl;
}

void L() {
	int number1 = result[2][0], number2 = result[2][1], number3 = result[2][2], number4 = result[0][1];
	result[2][0] = number4;
	result[2][1] = number1;
	result[2][2] = number2;
	result[0][1] = number3;
}

void R() {
	int number1 = result[2][0], number2 = result[2][1], number3 = result[2][2], number4 = result[0][1];
	result[2][0] = number2;
	result[2][1] = number3;
	result[2][2] = number4;
	result[0][1] = number1;
}

void F() {
	int number1 = result[0][1], number2 = result[1][1], number3 = result[2][1], number4 = result[3][1];
	result[0][1] = number2;
	result[1][1] = number3;
	result[2][1] = number4;
	result[3][1] = number1;
}

void B() {
	int number1 = result[0][1], number2 = result[1][1], number3 = result[2][1], number4 = result[3][1];
	result[0][1] = number4;
	result[1][1] = number1;
	result[2][1] = number2;
	result[3][1] = number3;
}

void A() {
	int number1 = result[1][1], number2 = result[2][0], number3 = result[3][1], number4 = result[2][2];
	result[1][1] = number4;
	result[2][0] = number1;
	result[3][1] = number2;
	result[2][2] = number3;
}

void C() {
	int number1 = result[1][1], number2 = result[2][0], number3 = result[3][1], number4 = result[2][2];
	result[1][1] = number2;
	result[2][0] = number3;
	result[3][1] = number4;
	result[2][2] = number1;
}

int main() {
	string input;
	cin >> input;
	for (int i = 0; i < input.size(); ++i) {
		char temp = input[i];
		if (temp == 'L') {
			L();
		}
		else if (temp == 'R') {
			R();
		}
		else if (temp == 'F') {
			F();
		}
		else if (temp == 'B') {
			B();
		}
		else if (temp == 'A') {
			A();
		}
		else if (temp == 'C') {
			C();
		}
	}
	CoutResult();
	system("pause");
	return 0;
}