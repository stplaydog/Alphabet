#include <vector>
#include <iostream>

using namespace std;


int find_k_th(vector<int> v, int l, int r, int k){
    
    int ll = l;
    int rr = r;

    int pv = l;
    int tmp = v[pv];
    while(l<r){
        while(v[l]<=v[pv] && l<r) l++;
        while(v[r]>=v[pv] && l<r) r--;
        if(l!=r) swap(v[l], v[r]);
    }
    v[l] = tmp; 

    if(l==k) return tmp;
    
    if(l>ll) find_k_th(v, ll, l-1, k);
    if(r<rr) find_k_th(v, r+1, rr, k);
}


int main(int argc, char *argv[]){
    vector<int> v = {1,3,2,8,6,4,7};
    int l(0), r=v.size()-1;
    cout<<"result is "<<find_k_th(v, l, r, 2)<<endl;
    return 1;
}

