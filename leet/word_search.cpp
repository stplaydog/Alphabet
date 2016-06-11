class Solution {
    public:
        bool exist(vector<vector<char>>& board, string word) {
            
        }

        void help(vector<vector<char>>& board, string word, int x, int y, int pos){
            char left = x>0 ? borad[y][x-1] : '\0';
            char right = x<board[y].size()-1 ? borad[y][x+1] : '\0';
            char up = y>0 ? borad[y-1][x] : '\0';
            char low = y<board.size()-1 ? borad[y+1][x] : '\0';
            if(left==)
        }
};
