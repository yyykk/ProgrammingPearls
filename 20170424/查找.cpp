/*
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
*/


class Solution {
public:
    //暴力查找
    bool Find1(int target, vector<vector<int> > array) {
        for (int i = 0; i < array.size(); ++i){
            for (int j  = 0; j < array[i].size(); ++j){
                if(array[i][j] == target){
                    return true;
                }
            }
        }
        return false;
    }
    //类二分查找
    bool Find2(int target, vector<vector<int> > array) {
        int i = array.size() - 1, j = 0;
        while(1){
            if(i < 0 || j == array[i].size()){
                return false;
            }else if (target == array[i][j]){
                return true;
            }else if (target < array[i][j]){
                i--;
            }else if (target > array[i][j]){
                j++;
            }
        }
    }
};