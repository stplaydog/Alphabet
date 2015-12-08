#include <iostream>
#include <cstdio>
#include <cstdlib>


using namespace std;

void print32_bit(int32_t num){
    int32_t mask = 1;
    string t;
    for(int i=0; i<32; i++){
        int tmp = mask & num;
        if(tmp>0)
           t = "1"+t;
        else
            t = "0"+t;
        mask = mask<<1;
    }
    cout<<t<<endl;
}

void print64_bit(int64_t num){
    int64_t mask = 1;
    string t;
    for(int i=0; i<64; i++){
        int64_t tmp = mask & num;
        if(tmp>0)
           t = "1"+t;
        else
            t = "0"+t;
        mask = mask<<1;
    }
    cout<<t<<endl;
}

int main(int argc, char *arv[]){
    enum GGPARAM_UNIT{
        GGPARAM_SEC = 1000
    };
    int64_t val = 18874367;

    int64_t tmp0 =  val * 1000;
    print64_bit(tmp0);

    int64_t tmp1 =  (int32_t) val * 1000;
    print64_bit(tmp1);

    //int32_t ret = (int32_t) val * 1000 / 1000;
    //cout<<ret<<" " << tmp0<<" "<<tmp1<<endl;
    return 0; 
}
