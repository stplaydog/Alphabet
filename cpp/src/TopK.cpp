#include "utils.h"

vector<int> topK(const vector<int> & input, int k)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i=0; i<input.size(); i++)
    {
        if(pq.size()==k)
        {
            if(input[i]>=pq.top())
            {
                pq.pop();
                pq.push(input[i]);
            }
        }
        else
            pq.push(input[i]);
    }
    vector<int> ret;
    while(!pq.empty())
    {
        int elem = pq.top();
        pq.pop();
        ret.push_back(elem);
    }
    return ret;
}

int main(int argc, char* argv[])
{
    vector<int> input;
    for(int i=0; i<1000; i++)
    {
        int val = rand() % 1000;
        input.push_back(val);
    }
    vector<int> min10 =  minK(input, 10);
    sort(input.begin(), input.end());
    Utils::dump(input);
    Utils::dump(min10);
    return 0;
}
