class Solution {
    public:
        bool isPowerOfTwo(int n) {
            if(n==0) return false;
            while(true)
             {
                 if(2*(n/2) == n)
                     n = n/2;
                 else
                     break;
             }
             if(n==1)
                 return true;
             else
                 return false;
        }
};
