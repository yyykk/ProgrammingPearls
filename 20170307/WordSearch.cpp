class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) 
    {
        if (board.empty() && word.empty()) return true;
        else if (board.empty()) return false;
 
        int row = board.size(), col = board[0].size();
        vector<vector<bool> > table(row, vector<bool>(col));
 
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if(onePosTest(board,table, word, 0, i, j)) 
                    return true;
            }
        }
        return false;
    }
 
    bool onePosTest(vector<vector<char> > &board, vector<vector<bool> > &table,
        string &word, int w_start, int i, int j) 
    {
        //ע�⣺�ж�˳������
        //���1�����磬����
        if (i>=board.size() || i <0 || j<0 || j>=board[0].size()) return false;
 
        //���3������ȣ����߱������˵ĵ㣬����table������false
        if (table[i][j] || board[i][j] != word[w_start]) return false;
 
        //���2�������û�������ĵ㣬��table��־λ��
        table[i][j] = true;
        //���4���ҵ���������������
        if (w_start == word.size()-1) return true;
 
        //��֧�ݹ飺
        if (onePosTest(board, table, word, w_start+1, i, j+1)
        ||  onePosTest(board, table, word, w_start+1, i+1, j)
        ||  onePosTest(board, table, word, w_start+1, i-1, j)
        ||  onePosTest(board, table, word, w_start+1, i, j-1))
        {
            return true;
        }
        table[i][j] = false;
        return false;
    }
};

class Solution {
public:
    bool dfs(vector<vector<char> > &board, string word, int count, int i, int j){
        if(count > word.size() || i > board.size() || j > board[0].size()){
            return false;
        }
        if()
    }
    
    bool exist(vector<vector<char> > &board, string word) {
        if(board.size() == 0){
            if(word.size() == 0){
                return true;
            }else{
                return false;
            }
        }
        int row = board.size();
        int col = board[0].size();
        vector
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                if(dfs(board, word, 0, i, j)){
                    return true;
                }
            }
        }
        return false;
    }
};

