#include <iostream>
#include "CSVparser.h"
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>
#include <queue>

using namespace std;

#define EPS 0.001

bool same(double a, double b) {
    bool ret = fabs(a - b) <= EPS; 
    return ret;
}


class PriceData 
{

public:

    struct Item{
        string symb;
        int    time;
        double bid;
        double ask;

        void dump()
        {
            cout<<symb.c_str()<<" "<<time<<" "<<bid<<" "<<ask<<endl;
        }
    };

    typedef map<int, vector<Item>>         pdata;
    typedef map<string, vector<int>>       smap;

    PriceData(const char * file)
    {
        csv::Parser f = csv::Parser(file);
        for(uint32_t i=0; i<f.rowCount(); i++)
        {
            int time = stoi(f[i][0]);
            Item itm;
            itm.time = time;
            itm.symb = f[i][1];
            itm.bid  = stof(f[i][2]); 
            itm.ask  = stof(f[i][3]); 
            //itm.dump();
            auto it = m_data.find(time);
            if(it == m_data.end())
            {
                vector<Item> v;
                v.push_back(itm);
                m_data[time] = v;
            }
            else
                it->second.push_back(itm);

            auto it1 = m_index.find(itm.symb);
            if(it1 == m_index.end())
            {
                vector<int> v;
                v.push_back(time);
                m_index[itm.symb] = v;
            }
            else
            {
                it1->second.push_back(time);
            }
        }

        for(auto i = m_index.begin(); i != m_index.end(); ++i)
            sort(i->second.begin(), i->second.end());
    }

    Item searchLatest(int time, string symb)
    {
        auto pos = lower_bound(m_index[symb].begin(), m_index[symb].end(), time);
        vector<Item> d = m_data[pos-m_index[symb].begin()];
        for(auto it = d.begin(); it != d.end(); ++it)
        {
            if(it->symb == symb)
            {
                return *it;
            }
        }
    }

    void dump()
    {
        for(auto it2 = m_data.begin(); it2 != m_data.end(); ++it2)
        {
            for(auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
            {
                it3->dump();
            }
            cout<<endl;
        }
        for(auto it4 = m_index.begin(); it4 != m_index.end(); ++it4)
        {
            cout<<it4->first<<" ";
            for(auto it5 = it4->second.begin(); it5!= it4->second.end(); ++it5)
            {
                cout<<*it5<<" ";
            }
            cout<<endl;
        }
    }

    pdata   m_data;
    smap    m_index;
};

class TradeData
{
public:

    struct Item{
        int    time;
        string symb;
        double price;
        int    quantity;

        string dump()
        {
            cout<<symb.c_str()<<" "<<time<<" "<<price<<" "<<quantity<<endl;
        }
    };

    typedef map<string, queue<Item>> inventory;

    TradeData(const char* file)
    {
        csv::Parser f = csv::Parser(file);
        for(uint32_t i=0; i<f.rowCount(); i++)
        {
            if(f[i][2] == "B")
            {
                Item itm;
                int time      = stoi(f[i][0]);
                itm.time      = time;
                itm.symb      = f[i][1];
                itm.price     = stof(f[i][3]); 
                itm.quantity  = stoi(f[i][4]); 
                itm.dump();
            }
            else
            {
            }
        }
    }

    void dump()
    {
    }

    inventory m_inv;
};


int main(int argc, char* argv[])
{
    PriceData p(argv[1]);    

    PriceData::Item item = p.searchLatest(2, string("ABC"));
    assert(item.time == 1 && true == same(item.bid, 10.05) && same(item.ask, 10.06) && item.symb == "ABC");

    TradeData t(argv[2]);
    return 0;
}
