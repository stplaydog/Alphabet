#include "utils.h" 

using namespace std;

class SetMatZero
{
public:
    SetMatZero(const vector<vector<int>> & mat)
        : m_mat(mat)
    {
        size_t nrow = mat.size();
        size_t ncol = mat[0].size();
        vector<int> row(nrow, 0);
        vector<int> col(ncol, 0);

        for(size_t i=0; i<nrow; i++)
        {
            for(size_t j=0; j<ncol; j++)
            {
                if(m_mat[i][j] == 0)
                {
                    row[i] = 1;
                    col[j] = 1;
                }
            }
        }

        for(size_t i=0; i<nrow; i++)
        {
            for(size_t j=0; j<ncol; j++)
            {
                if(row[i] == 0 || col[j] == 0)
                {
                    m_mat[i][j] = 0;
                }
            }
        }
        
        Utils::dump(m_mat);
    }

private:
    vector<vector<int>> m_mat;
};
