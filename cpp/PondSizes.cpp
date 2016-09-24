#include <iostream>
#include <cassert>
#include <vector>

using namespace std;


class PondSize
{
public:

    PondSize(const vector<vector<int> > &data)
    {
        m_data = data;
    }

    vector<int> calculate()
    {
        vector<int> ret;

        for(int i=0; i<m_data.size(); i++)
        {
            for(int j=0; j<m_data[0].size(); j++)
            {
                int size = cal_size(i, j);
                if(size) ret.push_back(size);
            }
        }
        sort(ret.begin(), ret.end());
        return ret;
    }

    int cal_size(int i, int j)
    {
        if(i<0 || j<0 || i>= m_data.size() || j>= m_data[0].size() || m_data[i][j] != 0)
            return 0;

        int ret = 1;
        m_data[i][j] = -1;

        for(int d1 = -1; d1<=1; d1++)
        {
            for(int d2 = -1; d2<= 1; d2++)
            {
                ret += cal_size(i+d1, j+d2);                
            }
        }
        return ret;
    }
private:
    vector<vector<int> > m_data;
};

int main(int argc, char* argv[])
{
    vector<vector<int> > d1{{0,2,1,0}, {0,1,0,1}, {1,1,0,1}, {0,1,0,1}};
    vector<vector<int> > d2{{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};

    PondSize p1(d1);
    PondSize p2(d2);
    
    vector<int> ret1{1,2,4}; 
    vector<int> ret2{16}; 
    assert(p1.calculate() == ret1);
    assert(p2.calculate() == ret2);
}
