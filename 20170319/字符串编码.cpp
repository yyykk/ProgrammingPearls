/*

����һ���ַ��������㽫�ַ������±��룬���������ַ��滻�ɡ��������ֵĸ���+�ַ����������ַ���AAAABCCDAA�ᱻ�����4A1B2C1D2A��

*/

#include "iostream"
#include "string"
using namespace std;
int main(){
    string input = "";
    string result = "";
    int amout = 0;
    char temp;
    while(cin >> input){
        int max = input.size();
        for(int i = 0; i < max; ++i){
            if(i == 0){
                temp = input[i];
                amout = 1;
            }else if(input[i] != temp){
                cout << amout << temp;
                amout = 1;
                temp = input[i];
            }else{
                ++amout;
            }
            if(i == max - 1){
                cout << amout << temp;
            }
        } 
    }  
}