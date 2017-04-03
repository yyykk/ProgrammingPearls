/*
给定一个字符串s，你可以从中删除一些字符，使得剩下的串是一个回文串。如何删除才能使得回文串最长呢？
输出需要删除的字符个数。
*/

#include "iostream"
#include "vector"
#include "algorithm"
#include "string"
using namespace std;

int lcs(string str1, string str2){
    int len1 = str1.size(), len2 = str2.size();
    vector<vector<int>> temp(len1 + 1, vector<int>(len2 + 1, 0));
    for(int i = 1; i <= len1; ++i){
        for(int j = 1; j <= len2; ++j){
            if (str1[i - 1] == str2[j - 1]){
                temp[i][j] = temp[i - 1][j - 1] + 1;
            }else{
                temp[i][j] = max(temp[i][j - 1], temp[i - 1][j]);
            }
        }
    }
    return temp[len1][len2];  
}

string re(string &str){
    string result = str;
    for(int i = str.size(); i > 0; --i){
        result[str.size() - i] = str[i - 1];
    }
    return result;
}

int main(){
    string str1, str2;
    while(cin >> str1){
        str2 = re(str1);
		cout << str1.size() - lcs(str1, str2) << endl;
    }
    return 0;
}

/*
把一个字符串的大写字母放到字符串的后面，各个字符的相对位置不变，且不能申请额外的空间。
*/

#include "iostream"
#include "string"

using namespace std;

int main(){
	string str1;
	while(cin >> str1){
        int len = str1.size();
		for(int i = 0; i < len; ++i){
			if(str1[i] >= 'A' && str1[i] <= 'Z'){
				char temp = str1[i];
				for(int j = i; j < str1.size() - 1; ++j){
					str1[j] = str1[j + 1];
				}
				str1[str1.size() - 1] = temp;
                i--;
                len--;
			}
		}
		cout << str1 << endl;
	}
}


/*
小Q今天在上厕所时想到了这个问题：有n个数，两两组成二元组，差最小的有多少对呢？差最大呢？
*/
#include "iostream"
#include "vector"
#include "algorithm"
#include "map"
using namespace std;

int main() {
	int n, temp;
    while(cin >> n){
    	map<int, int> m;
        for (int i = 0; i < n; ++i) {
            cin >> temp;
            m[temp]++;
        }
        if (n == 0) {
            cout << 0 << " " << 0 << endl;
        }
        else if (m.size() == 1) {
            cout << m.begin()->second * (m.begin()->second - 1) / 2 << " " << m.begin()->second * (m.begin()->second - 1) / 2 << endl;
        }
        else {
            map<int, int>::iterator mapTemp = m.begin(), endTemp = m.end();
            endTemp--;
            int minCounter = 0, maxCounter = 0, min = (++mapTemp)->first - m.begin()->first;
            for (map<int, int>::iterator i = m.begin(); i != m.end(); ++i) {
                if (i->second > 1) {
                    minCounter += i->second * (i->second - 1) / 2;
                }
            }
            if (minCounter == 0) {
                for (map<int, int>::iterator i = m.begin(); i != endTemp; ) {
                    mapTemp = i;
                    temp = (++i)->first - mapTemp->first;
                    if (temp <= min) min = temp;
                }
                for (map<int, int>::iterator i = m.begin(); i != endTemp; ) {
                    mapTemp = i;
                    temp = (++i)->first - mapTemp->first;
                    if (temp == min) minCounter += 1;
                }
            }
            mapTemp = m.end();
            cout << minCounter << " " << (--mapTemp)->second * m.begin()->second << endl;
        } 
    }
    return 0;
}









