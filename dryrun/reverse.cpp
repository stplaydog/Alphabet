/**
 * @brief     reverse a string
 * 
 * @param[out]     s      string to be reversed
 *
 * @return     N/A
 **/
void reverse(string s)
{
    int middle = s.size()/2;
    for(int i=0; i<middle; i++)
    {
        char tmp = s[i];
        s[i] = s[s.size()-i-1];
        s[s.size()-i-1] = tmp;
    }
}
