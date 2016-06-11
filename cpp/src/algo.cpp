/* Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.*/
/**
 * @brief    This is the class for cpp algorithms. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   06/11/16 - Creation
 *
**/

#include "./algo.h"
#include <algorithm>
#include <vector>
#include <iostream>

USING_NAMESPACE_YM_CPP

using namespace std;

void Algo::run_for_each()
{
    vector<int> v = {1, 2, 3, 4, 5};
    for_each(v.begin(), v.end(), print_t<int>);
}

template <typename T>
void Algo::print_t(T i)
{
    cout << i << " ";
}
