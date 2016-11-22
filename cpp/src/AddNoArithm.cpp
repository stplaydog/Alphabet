#include "utils.h"

int addNoArithm(int a, int b)
{
    if (b == 0) 
        return a;
    int sum = a ^ b; 
    int carry = (a & b) << 1; 
    cout<<sum<<" "<<carry<<endl;
    return addNoArithm(sum, carry);
}

int main(int argc, char* argv[])
{
    cout<<addNoArithm(10, 15)<<endl;
    return 0;
}
