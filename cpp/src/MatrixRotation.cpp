#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

//
// 1  2  3  4     | 13 9  5 1
// 5  6  7  8     | 14 10 6 2
// 9  10 11 12    | 15 11 7 3
// 13 14 15 16    | 16 12 8 4
//
// 1  2  3  4  5   | 21 16 11 6  1
// 6  7  8  9  10  | 22 17 12 7  2
// 11 12 13 14 15  | 23 18 13 8  3
// 16 17 18 19 20  | 24 19 14 9  4
// 21 22 23 24 25  | 25 20 15 10 5

class MatrixRotation
{
public:
    MatrixRotation(const vector<vector<int>> &mat)
        : m_mat(mat)
    {}

    void rotate()
    {
        int n = m_mat.size();
        for(int l=0; l<n/2; l++)
        {
            int end = n - l - 1;
            for(int i=l; i<end; i++)
            {
                int off = i - l;
                int tmp = m_mat[l][i];
                m_mat[l][i]         = m_mat[end-off][l];
                m_mat[end-off][l]   = m_mat[end][end-off]; 
                m_mat[end][end-off] = matrix[i][last];
                m_mat[i][end]       = tmp;
            }
        }
    }

    void dump()
    {
        for(int i=0; i<m_mat.size(); i++)
        {
            for(int j=0; j<m_mat[0].size(); j++)
            {
                cout<<m_mat[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    private:
    vector<vector<int>> m_mat;
};

int main(int argc, char* argv[])
{
    vector<vector<int>> m1 = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    MatrixRotation mr1(m1);
    mr1.dump();
    mr1.rotate();
    mr1.dump();

    vector<vector<int>> m2 = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25}};
    MatrixRotation mr2(m2);
    mr2.dump();
    mr2.rotate();
    mr2.dump();
    return 0;
}
