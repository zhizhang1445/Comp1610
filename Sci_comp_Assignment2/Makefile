# makefile for the wave1d application

all: wave1d

wave1d: wave1d_main.o wave1d_ex.o wave1d_io.o 
	g++ -std=c++17 -O2 -o wave1d wave1d_main.o wave1d_ex.o wave1d_io.o -lnetcdf_c++4 -lnetcdf

wave1d_main.o: wave1d_main.cpp
	g++ -c -std=c++17 -O2 -Wall -o wave1d_main.o wave1d_main.cpp

wave1d_ex.o: wave1d_ex.cpp
	g++ -c -std=c++17 -O2 -Wall -o wave1d_ex.o wave1d_ex.cpp

wave1d_io.o: wave1d_io.cpp
	g++ -c -std=c++17 -O2 -Wall -o wave1d_io.o wave1d_io.cpp

clean:
	$(RM) *.o

.PHONY: all clean

