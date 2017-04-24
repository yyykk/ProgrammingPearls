/*
请实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
*/

class Solution {
public:
	void replaceSpace(char *&str,int length) {
		int n = 0;
        for(int i = 0; i < length; ++i){
            if(str[i] == ' ') ++n;
        }
        char *result = new char[length + n * 2];
        int j = 0;
        for(int i = 0; i < strlen(str); ++i){
            if(str[i] != ' '){
                result[j] = str[i];
                j += 1;
            }else{
                result[j] = '%';
                result[j + 1] = '2';
                result[j + 2] = '0';
            	j += 3;
            }
        }
        result[length + n * 2 - 1] = '\0';
        str = result;
    }
};