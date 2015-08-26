/**
 *  @brief   quick sort algorithm for integer array.
 *  @param[out] num     array to be sorted
 *  @param[in] left        lower index
 *  @param[in]    right       upper index
 *
 *  @return     N/A
**/
void q_sort(int *num, int left, int right)
{
    int l_hold = left;
    int r_hold = right;
    int pivot = num[left];

    /* Shift elements */
    while(left < right)
    {
        while(num[right] >= pivot && left < right)
        {
            --right;
        }
        while(num[left] <= pivot && left < right)
        {
            ++left;
        }
        if(left != right)
        {
            int tmp = num[right];
            num[right] = num[left];
            num[left] = tmp;
        }
    }

    /* finalize pivot value */
    int pivot_pos = left;
    num[pivot_pos] = pivot;

    /* recursive sort sub-arrays */
    if(pivot_pos > l_hold)
    {
        q_sort(num, l_hold, pivot_pos -1);
    }
    if(pivot_pos < r_hold)
    {
        q_sort(num, pivot_pos +1, r_hold);
    }
}
