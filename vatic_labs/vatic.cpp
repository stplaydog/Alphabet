#include "CSVparser.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>
#include <queue>
#include <iomanip>

using namespace std;

#define EPS 0.001

bool same(double a, double b) 
{
    return fabs(a - b) <= EPS; 
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
        //dump();
    }

    Item searchLatest(int time, string symb)
    {
        auto pos = lower_bound(m_index[symb].begin(), m_index[symb].end(), time);
        int t    = pos-m_index[symb].begin();
        if(t==m_index[symb].size())
            t = m_index[symb][m_index[symb].size()-1];
        vector<Item> d = m_data[t];
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
        string side;

        void dump()
        {
            cout<<symb.c_str()<<" "<<side<<" "<<time<<" "<<price<<" "<<quantity<<endl;
        }
    };

    typedef map<string, queue<Item>> inventory;

    TradeData(const char* priceFile, const char *file)
        : m_data(priceFile)
    {
        csv::Parser f = csv::Parser(file);
        for(uint32_t i=0; i<f.rowCount(); i++)
        {
            Item itm;
            int time      = stoi(f[i][0]);
            itm.time      = time;
            itm.symb      = f[i][1];
            itm.side      = f[i][2];
            itm.price     = stof(f[i][3]); 
            itm.quantity  = stoi(f[i][4]); 

            if(f[i][2] == "B")
            {
                if(!check_finish(itm, m_pend))
                    place_item(itm, m_inv);
            }
            else
            {
                if(!check_finish(itm, m_inv))
                    place_item(itm, m_pend);
            }
            //dump();
        }
    }

    bool check_finish(Item & itm, inventory & inv)
    {
        auto it = inv.find(itm.symb);
        if(it == inv.end())
            return false;
        else
        {
            queue<Item> &q = inv[itm.symb];
            while(itm.quantity && !q.empty())
            {
                Item &elem = q.front();
                int diff = itm.quantity - elem.quantity;
                print_record(elem, itm);
                if(diff == 0)
                {
                    q.pop();
                    itm.quantity    = 0;
                    break;
                }
                else if(diff < 0)
                {
                    elem.quantity  -= itm.quantity;
                    itm.quantity    = 0;
                    break;
                }
                else if(diff > 0)
                {
                    itm.quantity    = diff; 
                    q.pop();
                }
            }
            if(itm.quantity)
                return false;
        }
        return true;
    }

    void print_record(Item & a, Item & b)
    {
        int ot      = a.time;
        int ct      = b.time;
        string symb = a.symb;
        int qt      = a.quantity>b.quantity ? b.quantity : a.quantity;
        double PNL  = calPNL(a, b, qt);
        string os   = a.side;
        string cs   = b.side;
        double op   = a.price;
        double cp   = b.price;

        PriceData::Item oit = m_data.searchLatest(a.time, a.symb);
        double ob   = oit.bid; 
        double oa   = oit.ask; 

        PriceData::Item cit = m_data.searchLatest(b.time, b.symb);
        double cb   = cit.bid; 
        double ca   = cit.ask; 

        string ol   = getLiquidity(a.side, op, ob, oa);
        string cl   = getLiquidity(b.side, cp, cb, ca);


        cout<<fixed;
        cout<<setprecision(2);;
        cout<<ot<<","<<ct <<","<<symb<<","
            <<qt<<","<<PNL<<","
            <<os<<","<<cs <<","
            <<op<<","<<cp <<","
            <<ob<<","<<cb <<","
            <<oa<<","<<ca <<","
            <<ol<<","<<cl 
            <<endl;
    }

    string getLiquidity(string &type, double price, double bid, double ask)
    {
        if(type == "B")
        {
            return price <= bid ? "P" : "A";
        }
        else
        {
            return price >= ask ? "P" : "A";
        }
    }

    double calPNL(Item & a, Item & b, int qt)
    {
        double buy;
        double sell;
        if(a.side == "B")
        {
            buy  = a.price;
            sell = b.price;
        }
        else
        {
            buy  = b.price;
            sell = a.price;
        }
        return (sell- buy)*qt;
    }


    void place_item(const Item & itm, inventory & inv)
    {
        auto it = inv.find(itm.symb);
        if(it == inv.end())
        {
            queue<Item> q;
            q.push(itm);
            inv[itm.symb] = q;
        }
        else
            it->second.push(itm);
    }

    void dump()
    {
        cout<<"inventory:"<<endl;
        for(auto it = m_inv.begin(); it != m_inv.end(); ++it)
        {
            for(int i=0; i<it->second.size(); i++)
            {
                Item itm = it->second.front();
                it->second.pop();
                itm.dump();
                it->second.push(itm);
            }
        }

        cout<<"buying:"<<endl;
        for(auto it = m_pend.begin(); it != m_pend.end(); ++it)
        {
            for(int i=0; i<it->second.size(); i++)
            {
                Item itm = it->second.front();
                it->second.pop();
                itm.dump();
                it->second.push(itm);
            }
        }

        cout<<"====="<<endl;
    }

    inventory m_inv;
    inventory m_pend;
    PriceData m_data;
};


int main(int argc, char* argv[])
{
    TradeData t(argv[1], argv[2]);

    //TradeData t1("quo.csv", "trd.csv");
    //PriceData::Item item = t1.m_data.searchLatest(2, string("ABC"));
    //assert(item.time == 1 && true == same(item.bid, 10.05) && same(item.ask, 10.06) && item.symb == "ABC");

    return 0;
}
