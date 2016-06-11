noinst_HEADERS= algo.h carray.h 
bin_PROGRAMS=cpplearn
cpplearn_SOURCES= algo.cpp carray.cpp main.cpp
if DEBUG
AM_CXXFLAGS = -g  -I$(top_srcdir)/libs -D__USE_XOPEN2K8 -lglog -std=c++11 -Wall 
else
AM_CXXFLAGS = -g -I$(top_srcdir)/libs -DUSE_DEBUG -D__USE_XOPEN2K8 -lglog -std=c++11 -Wall 
endif
