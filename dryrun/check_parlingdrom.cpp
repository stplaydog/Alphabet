#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cassert>
#include <iostream>

using namespace std;

bool check_palingdrom(int64_t num)
{
    int64_t tmp = num;
    int64_t reversed = 0;
    while(tmp >0)
    {
        int32_t residue = tmp % 10;
        tmp = tmp / 10;
        reversed *= 10;
        reversed += residue;
    }
    return reversed == num ? true : false;
}

int main(int argc, char* argv[])
{
    int64_t num = 123454321;
    assert(check_palingdrom(num) == true);


    num = 1232231;
    assert(check_palingdrom(num) == false);

    return 1;
}
