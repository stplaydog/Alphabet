#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>
#include <queue>
#include <iomanip>
#include <fstream>

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

        bool operator<(const Item& a) const
        {
            return symb < a.symb;
        }
    };


    typedef map<int, vector<Item>>         pdata;
    typedef map<string, vector<int>>       smap;

    PriceData(const char * file)
    {
        ifstream infile(file);
        int i=0;
        string line;
        while(getline(infile, line))
        {
            if(i++ == 0)
                continue;
            stringstream linestream(line);
            string f[4];

            getline(linestream, f[0], ',');
            getline(linestream, f[1], ',');
            getline(linestream, f[2], ',');
            getline(linestream, f[3], ',');

            int time = stoi(f[0]);
            Item itm;
            itm.time = time;
            itm.symb = f[1];
            itm.bid  = stof(f[2]); 
            itm.ask  = stof(f[3]); 
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

        for(auto i = m_data.begin(); i != m_data.end(); ++i)
            sort(i->second.begin(), i->second.end());
        dump();
    }

    Item searchLatest(int time, string symb)
    {
        Item ret;
        ret.symb = symb;
        auto pos = lower_bound(m_index[symb].begin(), m_index[symb].end(), time);
        int tt = *pos == time ? time : *prev(pos);
        ret = *lower_bound(m_data[tt].begin(), m_data[tt].end(), ret);
        return ret;
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
        ifstream infile(file);
        int i=0;
        string line;

        while(getline(infile, line))
        {
            if(i++ == 0)
            {
                cout<<"OPEN_TIME,CLOSE_TIME,SYMBOL,QUANTITY,PNL,OPEN_SIDE,CLOSE_SIDE,OPEN_PRICE,CLOSE_PRICE,OPEN_BID,CLOSE_BID,OPEN_ASK,CLOSE_ASK,OPEN_LIQUIDITY,CLOSE_LIQUIDITY"<<endl;
                continue;
            }
            stringstream linestream(line);
            string f[5];

            getline(linestream, f[0], ',');
            getline(linestream, f[1], ',');
            getline(linestream, f[2], ',');
            getline(linestream, f[3], ',');
            getline(linestream, f[4], ',');

            Item itm;
            int time      = stoi(f[0]);
            itm.time      = time;
            itm.symb      = f[1];
            itm.side      = f[2];
            itm.price     = stof(f[3]); 
            itm.quantity  = stoi(f[4]); 

            if(f[2] == "B")
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
        //cout<<"price:"<<price<<" type:"<<type<<" bid:"<<bid<<" ask:"<<ask<<endl;
        if(type == "B")
        {
            if (price <= bid) 
                return "P"; 
            else if(price >= ask)
                return "A";
        }
        else
        {
            if (price >= ask) 
                return "P"; 
            else if(price <= bid)
                return "A";
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
        return fabs((sell- buy)*qt);
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
    return 0;
}
