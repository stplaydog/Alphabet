#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cassert>
#include <iostream>

using namespace std;

void merge(int *num, int mid, int left, int right)
{
    int *tmp = new int[right-left+1];
    int tmp_pos = 0;
    int l = left;
    int m = mid;

    /* merge */
    while(l<m && right>m)
    {
        if(num[l] < num[m] && l < m)
        {
            tmp[tmp_pos++] = num[l];
            ++l;
        }
        else if(num[m] < num[l] && m < right)
        {
            tmp[tmp_pos++] = num[m];
            ++m;
        }
    }

    /* left over */
    if(l>mid)
    {
        for(int i=m; i<=right; i++)
        {
            tmp[tmp_pos++] = num[i];
        }
    }
    else
    {
        for(int i=l; i<=mid; i++)
        {
            tmp[tmp_pos++] = num[i];
        }
    }

    /* copy back */
    for(int i=0; i<right-left+1; i++)
    {
        num[i+left] = tmp[i];
    }


    free(tmp);
}

void m_sort(int *num, int left, int right)
{
    int mid;
    if(left < right)
    {
        mid = (right-left)/2 + 1;
        m_sort(num, left, mid);
        m_sort(num, mid+1, right);
        merge(num,left, mid, right);
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

    m_sort(arr, 0, 9);

    string ret = "";
    for(int i=0; i<10; i++)
    {
        char str[100];
        snprintf(str, 100, "%d,", arr[i]);
        ret += str;
    }
    assert(strcmp(ret.c_str(), "1,2,3,4,5,6,7,8,9,10,") == 0);
}
