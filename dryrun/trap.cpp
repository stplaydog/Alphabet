class Solution {
    public:
        int trap(vector<int>& height) {
             map<pair<int, int>, int> &m;
             fill_dark(m, height);
             int l=0,r=1;
             int total;
             while(l<height.size()){
                while(height[l]>height[r]) j++;
                fill_water(m, l, r, height[l], total);
                l=r;
             }
             return total;
        }

    void fill_dark(map<pair<int, int>, int> &m, vector<int> h){
        for(int i=0; i<h.size(); i++){
            for(int j=0; j<h[i]; j++){
                pair<int, int> p(i, j);
                m[p] = 0;
            }
        }
    }

    void fill_water(map<pair<int, int>, int> &m, int l, int r, int h, int &total){
        for(int i=l, i<r; i++){
            for(int j=0; j<h; j++){
                pair<int, int> p(i, j);
                if(m.find(p) == m.end()){
                    m[p] = 1;
                    total++;
                }
            }
        }
    }
};
