/* Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.*/
/**
 * @brief    This is the class for cpp algorithms. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   05/31/16 - Creation
 *
**/

#pragma once
#ifndef _H_CARRAY
#define _H_CARRAY

#include "./nspace.h"

YM_CPP_NAMESPACE_BEGIN

/**
 * @class Algo 
 *
 * This class tests some CPP algorithms 
 *
**/
class CArray
{
 public:
     void release();

 private:
     struct s_arr
     {
         int a;
         int b;
         int c;
     };

     struct s_parr
     {
         int a;
         int b;
         int c;
         int *d;

         s_parr()
         {
             d = new int[100];
         }
     };
};

YM_CPP_NAMESPACE_END

#endif
