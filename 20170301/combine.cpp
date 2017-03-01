/*

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
For example,
If n = 4 and k = 2, a solution is:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

*/

class Solution {
public:
    void com(vector<vector<int> > &v, vector<int> temp, int n, int k, int start){
        if(temp.size() == k){
            v.push_back(temp);
            return;
        }
        for(int i = start; i <= n; ++i){
            temp.push_back(i);
            com(v, temp, n, k, i+1);
            temp.pop_back();
        }
    }
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int> > v;
        vector<int> temp;
        if(k > n || n == 0){
            return v;
        }else{
            com(v, temp, n, k, 1);
            return v;
        }
        
    }
};