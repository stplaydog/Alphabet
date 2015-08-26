void b_sort(int *num, int start, int end)
{
    for(int i=start; i<end; i++)
    {
        for(int j=i+1; j<end; j++)
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

