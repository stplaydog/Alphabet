/* Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.*/
/**
 * @brief    This is the class for cpp algorithms. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   06/11/16 - Creation
 *
**/

#include "./carray.h"

USING_NAMESPACE_YM_CPP

void CArray::release()
{
    s_arr  *aa = new s_arr[100];
    s_parr *ab = new s_parr[100];

    delete [] aa;
    delete [] ab;
}
