#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cassert>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<vector<int>> v(triangle);
        v[0][0] = triangle[0][0];
        for(int i=1; i<triangle.size(); i++){
            v[i][0] = v[i-1][0] + triangle[i][0]; 
            v[i][v[i].size()-1] = v[i-1][v[i].size()-1] + triangle[i][v[i].size()-1]; 
        }
        for(int i=1; i<triangle.size(); i++){
            for(int j=1; j<triangle[i].size()-1; j++){
                v[i][j] = triangle[i][j] + min(v[i-1][j-1], v[i-1][j]);
            }
        }
        return min_element(v.back().begin(), v.back().end());
    }
};

int main(int argc, char *argv[]){

    return 1;
}
