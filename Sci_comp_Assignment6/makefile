CXX=g++ 
CXXFLAGS=-std=c++17 -O2
RFLAGS=--log_level=all

all: gw_main

gw_main: gw_main.o gw_analysis.o gw_io.o
	${CXX} ${CXXFLAGS} -o gw_main gw_main.o gw_analysis.o gw_io.o -lnetcdf_c++4 -lnetcdf -lfftw3

gw_main.o: gw_main.cpp
	${CXX} ${CXXFLAGS} -c -o gw_main.o gw_main.cpp

gw_analysis.o: gw_analysis.cpp
	${CXX} ${CXXFLAGS} -c -o gw_analysis.o gw_analysis.cpp

gw_io.o: gw_io.cpp
	${CXX} ${CXXFLAGS} -c -o gw_io.o gw_io.cpp

clean:
	${RM} *.o

.PHONY: all clean