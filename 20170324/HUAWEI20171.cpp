#include "iostream"
#include "sstream"
using namespace std;

string IntString(int n)
{
	ostringstream stream;
	stream << n;
	return stream.str();
}

int StringInt(string n) {
	int number;
	stringstream s;
	s << n;
	s >> number;
	cout << number << endl;
	return number;
}

int reverseAdd(int a, int b) {
	string aa = IntString(a);
	string bb = IntString(b);
	string TempA = aa;
	string TempB = bb;
	for (int i = aa.size() - 1; i >= 0; --i) {
		TempA[aa.size() - 1 - i] = aa[i];
	}
	for (int i = bb.size() - 1; i >= 0; --i) {
		TempB[bb.size() - 1 - i] = bb[i];
	}
	return StringInt(TempA) + StringInt(TempB);
}

int main() {
	int a, b;
	cin >> a >> b;
	cout << reverseAdd(a, b) << endl;
	return 0;
}