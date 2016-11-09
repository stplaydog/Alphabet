#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cassert>
#include <iostream>


using namespace std;

int64_t get_max(string note)
{
    int64_t ret = -1;
    string tmp = "";
    for(int i=0; i<note.length(); i++)
    {
        if(note[i] == '?')
        {
            tmp+="9";
        }
        else
        {
            tmp += note[i];
        }
    }
    ret = atol(tmp.c_str());
    return ret; 
}

int64_t match(int64_t one, int64_t two, string note)
{
    int64_t sum = one + two;
    int64_t ret = sum;

    char sum_string[64];
    snprintf(sum_string, 64, "%lld", sum);
    string s_s(sum_string);

    if(s_s.length() != note.length())
    {
        ret = -1;
    }
    else
    {
        for(int i =0; i<s_s.length(); i++)
        {
            if(s_s[i] != note[i] && note[i] != '?')
            {
                ret = -1;
                break;
            }
        }
    }
    return ret;
}

int64_t min(int64_t one, int64_t two, int64_t three, int64_t four)
{
    if((one<two||two==-1) 
        && (one <three || three == -1) 
        && (one<four || four == -1))
        return one;
    if((two<one||one==-1) 
        && (two <three || three == -1) 
        && (two<four || four == -1))
        return two;
    if((three<one||one==-1) 
        && (three <two || two == -1) 
        && (three<four || four == -1))
        return three;
    else
        return four;
}

int64_t check_comb(int64_t one, int64_t two, string note)
{
    int64_t sum = one + two;
    int64_t ret = match(one, two, note);
    if(ret == -1 && one+two*10<get_max(note))
    {
        ret = check_comb(one, two*10+4, note);
    }
    if(ret == -1 && one+two*10<get_max(note))
    {
        ret = check_comb(one, two*10+7, note);
    }
    return ret;
}

int64_t dfs(int64_t one, string note)
{
    int64_t ret3=-1, ret4=-1;
    int64_t ret1 = check_comb(one, 4, note);
    int64_t ret2 = check_comb(one, 7, note);


    if(one*10 < get_max(note))
    {
        ret3 = dfs(one*10+4, note);
        ret4 = dfs(one*10+7, note);
    }

    return min(ret1, ret2, ret3, ret4);
}

int64_t check(string note)
{
    int64_t ret1 = -1, ret2 = -1;
    ret1 = dfs(4, note);
    ret2 = dfs(7, note);
    if(ret1 == -1 && ret2 != -1)
        return ret2;
    if(ret1 != -1 && ret2 == -1)
        return ret1;
    return ret1<ret2 ? ret1:ret2;
}

int main(int argc, char* argv[])
{

    string note = "?";
    int64_t ret = check(note);
    assert(ret == 8);

    note = "?1";
    ret = check(note);
    assert(ret == 11);

    note = "4?8";
    ret = check(note);
    assert(ret == 448);

    note = "2??";
    ret = check(note);
    assert(ret == -1);

    note = "??????????????";
    ret = check(note);
    assert(ret == 11888888888888);

    return 1;
}
