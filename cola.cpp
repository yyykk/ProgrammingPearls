/*

������һ�������⣺��ĳ�̵�涨����������ˮƿ���Ի�һƿ��ˮ��
С��������ʮ������ˮƿ���������Ի�����ƿ��ˮ�ȣ�������5ƿ��
�������£�����9����ƿ�ӻ�3ƿ��ˮ���ȵ�3ƿ���ģ������Ժ�4����ƿ�ӣ���3���ٻ�һƿ���ȵ���ƿ���ģ���ʱ��ʣ2����ƿ�ӡ�Ȼ�������ϰ��Ƚ����һƿ��ˮ���ȵ���ƿ���ģ������Ժ���3����ƿ�ӻ�һƿ���Ļ����ϰ塣
���С��������n������ˮƿ�������Ի�����ƿ��ˮ�ȣ�

*/
#include "iostream"
using namespace std;
int main(){
    int num;
    int temp;
    int amount;
    while(cin >> num && num != 0){
            temp = num;
            amount = 0;
            while(temp > 2){
                amount += temp / 3;
                temp = temp % 3 + temp / 3;
            }
            if(temp == 2){
                cout << amount + 1 << endl;
            }else{
                cout << amount << endl;
            }
    }
    return 0;
}