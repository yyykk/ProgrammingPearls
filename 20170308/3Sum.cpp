class Solution {
public:
    void Find3Sum(vector<vector<int>> &result, vector<int> &num, int i, int point) {
        int l = i, r = num.size() - 1;
        while (l < r) {
            if (point + num[l] + num[r] == 0) {
                result.push_back({point, num[l], num[r]});
                while (l < r && num[l] == num[l + 1]) {
                	++l;
                }
                while (l < r && num[r] == num[r - 1]) {
                    --r;
                }
                ++l;
                --r;
            }else if (point + num[l] + num[r] < 0) {
                ++l;
            }else if (point + num[l] + num[r] > 0) {
                --r;
            }
        }
    }
    vector<vector<int> > threeSum(vector<int> &num) {
        vector<vector<int>> result;
        sort(num.begin(), num.end());
        for (int i = 0; i < num.size(); ++i) {
            while(i > 0 && num[i] == num[i - 1]){
                ++i;
            }
            Find3Sum(result, num, i + 1, num[i]);
        }
        return result;
    }
};