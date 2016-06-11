/* Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.*/
/**
 * @brief    This is the class for cpp algorithms. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   05/31/16 - Creation
 *
**/

#pragma once
#ifndef _H_ALGO
#define _H_ALGO

#include "./nspace.h"

YM_CPP_NAMESPACE_BEGIN

/**
 * @class Algo 
 *
 * This class tests some CPP algorithms 
 *
**/
class Algo
{
 public:
     void run_for_each();

 private:
     template <typename T>
     static void print_t(T i);
};

YM_CPP_NAMESPACE_END

#endif
