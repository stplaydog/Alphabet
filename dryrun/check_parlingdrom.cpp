bool check_palingdrom(int num)
{
    int tmp = num;
    int reversed = 0;
    while(num >0)
    {
        residue = tmp % 10;
        tmp = tmp / 10;
        reverse *= 10;
        reverse += residue;
    }
    return reverse == num ? true : false;
}

