#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cassert>
#include <iostream>

using namespace std;

bool match(int64_t one, int64_t two, string note)
{
    bool ret = true;

    int64_t sum = one + two;
    char sum_string[64];
    snprintf(sum_string, 64, "%d", sum);
    string s_s(sum_string);

    if(s_s.length() != note.length())
    {
        ret = false;
    }
    else
    {
        for(int i =0; i<s_s.length(); i++)
        {
            if(s_s[i] != note[i] && note[i] != '?')
            {
                ret = false;
                break;
            }
        }
    }
    return ret;
}

int64_t check_comb(int64_t one, string note)
{
    int64_t depth = 0;
    int64_t two = 0;
    bool back_trace = false;
    int64_t last_try = -1;
    int64_t ret = -1;

    while(depth<note.length())
    {
        /* check two here */
        if (match(one, two, note))
        {
            ret = one + two;
            break;
        }

        if(back_trace == false)
        {
            two = two * 10 + 4;
        }
        else if(last_try == 4)
        {
            two = two *10 + 7;
            back_trace = false;
        }
        else
        {
            two = two / 10;
            back_trace = true;
            last_try = two % 10;
        }
        return ret;
    }
}

int64_t dfs(string note)
{
    int64_t depth = 0;
    int64_t one = 0;
    bool back_trace = false;
    int64_t last_try = -1;
    int64_t ret = -1;

    while(depth<note.length())
    {
        /* check one here */
        int64_t comb = check_comb(one, note);
        if(comb != -1)
        {
            ret = comb;
            break;
        }

        if(back_trace == false)
        {
            one = one * 10 + 4;
        }
        else if(last_try == 4)
        {
            one = one *10 + 7;
            back_trace = false;
        }
        else
        {
            one = one / 10;
            back_trace = true;
            last_try = one % 10;
        }
    }
    return ret;
}

int main(int argc, char* argv[])
{

    string note = "?";
    int64_t ret = dfs(note);
    assert(ret == 8);

    string note = "?1";
    int64_t ret = dfs(note);
    assert(ret == 11);

    string note = "4?8";
    int64_t ret = dfs(note);
    assert(ret == 448);

    string note = "2??";
    int64_t ret = dfs(note);
    assert(ret == -1);

    string note = "??????????????"
    int64_t ret = dfs(note);
    assert(ret == 11888888888888);

    return 1;
}
