noinst_PROGRAMS = cpptest
cpptest_SOURCES= gt_algo.cpp ../src/algo.cpp \
				 gt_cclass.cpp
TESTS=cpptest

if DEBUG
AM_CXXFLAGS = -g  -I$(top_srcdir)/src -I/usr/local/include -D__USE_XOPEN2K8 -lgtest_main -lgtest -DUSE_GTEST -lglog -std=c++11 -Wall -lboost_unit_test_framework-mt 
else
AM_CXXFLAGS = -g -I$(top_srcdir)/src -I/usr/local/include -DUSE_DEBUG -D__USE_XOPEN2K8 -lgtest_main -lgtest -DUSE_GTEST -lglog -std=c++11 -Wall -lboost_unit_test_framework-mt
endif
