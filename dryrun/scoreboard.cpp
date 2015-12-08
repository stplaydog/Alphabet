#include <map>
#include <string>
#include <set>
#include <iostream>
#include <cstdlib>

using namespace std;

class ScoreB{
    map<string, int> dir;
    map<int, set<string> > lead;

public:
    ScoreB(){
    }
    
    void add_win(string name){
        if(dir.find(name) == dir.end()){
            dir[name] = 1;
            lead[1].insert(name);
        }
        else{
            auto old = lead[dir[name]];
            old.erase(name);
            dir[name] += 1;
            auto l = lead[dir[name]];
            l.insert(name);
        }
    }

    void show_dir(){
        for(auto it = dir.begin(); it != dir.end(); it++){
            cout<<"name: "<<it->first<<" "<<it->second<<endl;
        }
    }

    void show_leader(){
        for(auto it = lead.begin(); it != lead.end(); ++it){
            auto st = it->second;
            for(auto ii = st.begin(); ii != st.end(); ++ii){
                cout<<"name: "<< *ii<< " score: "<< it->first<<endl;
            }
        }
    }
};


int main(int argc, char *argv[]){

    ScoreB s;
    s.add_win("arvind");
    s.add_win("arvind");
    s.add_win("arvind");
    s.add_win("zhaoming");
    s.add_win("zhaoming");
    s.add_win("zhaoming");
    s.add_win("zhaoming");
    s.add_win("zhaoming");
    s.add_win("zhaoming");
    s.add_win("arvind");

    s.show_dir();

    s.show_leader();

    return 1;
}
