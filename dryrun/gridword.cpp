#include <map>
#include <string>
#include <set>
#include <iostream>
#include <cstdlib>

using namespace std;

class Grid{

public:
    vector<vector<char>> grid;
    vector<vector<bool>> visited;

    Grid(int n, int m){
        for(int i=0; i<n; i++){
            grid.push_back(vector<char>(m));
            visited.push_back(vector<bool>(m), false);
        }
    }

    void set(int x, int y, char w){
        grid[y][x] = w;
    }

    bool contains(string word){
        bool res = false;
        for(int i=0; i<grid.size(); i++){
            for(int j=0; j<grid[i].size(); j++){
                if(dfs(word, 0, j, i))
                    return true;
            }
        }
        return false;
    }

    bool dfs(string &word, int pos, int x, int y){
        if(pos == word.length())
                return true;
        if(visited[y][x])
            return false;
        if(word[pos] != grid[y][x] )
            return false;

        bool ret = false;

        int l = x == 0 ? -1 : x -1;
        int r = x == grid[0].size()-1 ? -1 : x+1;
        int u = y == 0 ? -1 : y -1;
        int d = y == grid.size()-1 ? -1 : y+1;
        visited[y][x] = true;
        if(l != -1)
        {
            if(dfs(word, pos + 1, l, y))
                return ret;
        }
        if(r != -1)
        {
            if(dfs(word, pos + 1, r,y))
                return ret;
        }
        if(u != -1)
        {
            if(dfs(word, pos + 1, x, u))
                return ret;
        }
        if(d != -1)
        {
            if(dfs(word, pos + 1, x, d))
                return ret;
        }
        visited[y][x] = false;
        return false;
    }
};


int main(int argc, char *argv[]){


    return 1;
}
