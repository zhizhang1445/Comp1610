# makefile for the analysewave application

CXX=g++
CXX2=mpicxx
CXXFLAGS=-std=c++17 -g -O2 -Wall -Wno-unused-variable -fopenmp
CXXFLAGS2=-O2 -std=c++17 -march=native
LDFLAGS=-O2 -g
LDLIBS=-lnetcdf_c++4 -lnetcdf -fopenmp

all:analysewave analysewave_omp analysewave_mpi

OBJFILES=analysewave.o analysewave_omp.o analysewave_mpi.o

analysewave: analysewave.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

analysewave.o: analysewave.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

analysewave_omp: analysewave_omp.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

analysewave_omp.o : analysewave_omp.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

analysewave_mpi: analysewave_mpi.o
	$(CXX2) $(CXXFLAGS2) -o $@ $^ $(LDLIBS)

analysewave_mpi.o : analysewave_mpi.cpp
	$(CXX2) $(CXXFLAGS2) -c -o $@ $^

# customary clean rule(s):
clean:
	$(RM) $(OBJFILES)

distclean: clean
	$(RM) analysewave analysewave_omp analysewave_mpi
	$(RM) *.o

.PHONY: all clean distclean

