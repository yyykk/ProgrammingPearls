class Solution {
public:
    bool dfs(vector<vector<char> > &board, vector<vector<bool> > &visited,
             string &word, int count, int i, int j){
        if(i > board.size() || j > board[0].size() || i < 0 || j < 0){
            return false;
        }
        if(visited[i][j] || board[i][j] != word[count]){
            return false;
        }
        visited[i][j] = true;
        if(count == int(word.size()) - 1){
            return true;
        }
        if(dfs(board, visited, word, count + 1, i, j + 1)
          || dfs(board, visited, word, count + 1, i + 1, j)
          || dfs(board, visited, word, count + 1, i - 1, j)
          || dfs(board, visited, word, count + 1, i, j - 1)){
            return true;
        }
        visited[i][j] = false;
        return false;
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
        vector<vector<bool> > visited(row, vector<bool>(col, false));
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                if(dfs(board, visited, word, 0, i, j)){
                    return true;
                }
            }
        }
        return false;
    }
};

