#include "utils.h"

void reverseWords(string &s) {
    if(s == "") return;
    reverse(s.begin(), s.end());
    int m=0, n=s.length()-1;
    for(int i=0; i<s.length(); i++)
    {
        if(s[i] == ' ')
        {
            if(m<i)
            {
                reverse(s.begin()+m, s.begin()+i);
            }
            m = i+1;
        }
    }
    m=0;
    while(s[m] == ' ') m++;
    while(s[n] == ' ') n--;
    if(n<m) s="";
    if(m<=n)
        s = s.substr(m, n-m+1);
}


int main(int argc, char* argv[])
{
    string s1 = " ";
    reverseWords(s1);
    cout<< "\"" <<s1<< "\"" <<endl;

    string s2 = "  ";
    reverseWords(s2);
    cout<<"\""<<s2<<"\""<<endl;

    string s3 = " abc def ";
    reverseWords(s3);
    cout<<"\""<<s3<<"\""<<endl;

    string s4 = "abc     def ";
    reverseWords(s4);
    cout<<"\""<<s4<<"\""<<endl;
    return 0;
}
