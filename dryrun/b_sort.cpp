#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cassert>
#include <iostream>

using namespace std;

void b_sort(int *num, int start, int end)
{
    for(int i=end; i>=start; i--)
    {
        for(int j=start+1; j<=i; j++)
        {
            if(num[j-1] > num[j])
            {
                int tmp = num[j-1];
                num[j-1] = num[j];
                num[j] = tmp;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    int arr[10];
    arr[0] = 7;
    arr[1] = 4;
    arr[2] = 1;
    arr[3] = 3;
    arr[4] = 2;
    arr[5] = 5;
    arr[6] = 10;
    arr[7] = 8;
    arr[8] = 9;
    arr[9] = 6;

    b_sort(arr, 0, 9);

    string ret = "";
    for(int i=0; i<10; i++)
    {
        char str[100];
        snprintf(str, 100, "%d,", arr[i]);
        ret += str;
    }
    assert(strcmp(ret.c_str(), "1,2,3,4,5,6,7,8,9,10,") == 0);
}
