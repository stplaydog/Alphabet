/**
 * @brief    this is the merge sort algorithm.
 *
 * @param[out]    num    array to be sorted
 * @param[in]     left   left position
 * @param[in]     right  right position
 *
 * @return    N/A
 **/
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

/**
 * @brief    merge sorted sub-arrays
 * 
 * @param[out]    num    array to be sorted
 * @param[in]     mid    mid position separating two sorted arrays
 * @param[in]     left   left position
 * @param[in]     right  right position
 **/
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
