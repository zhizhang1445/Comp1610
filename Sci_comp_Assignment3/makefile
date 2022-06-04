all: grav_Part1 grav_Part2 grav_Part3

grav_Part1: grav_Part1_main.o grav_inter.o
	g++ -std=c++17 -O2 -o grav_Part1 grav_Part1_main.o grav_inter.o -lgsl -lgslcblas

grav_Part2: grav_Part2_main.o grav_inter.o grav_Part2_ex.o
	g++ -std=c++17 -O2 -o grav_Part2 grav_Part2_main.o grav_inter.o grav_Part2_ex.o -lgsl -lgslcblas

grav_Part3: grav_Part3_main.o grav_Part3_ex.o
	g++ -std=c++17 -O2 -o grav_Part3 grav_Part3_main.o grav_Part3_ex.o -lgsl -lgslcblas
# g++ -std=c++17 -O2 -o wave1d wave1d_main.o wave1d_ex.o wave1d_io.o -lnetcdf_c++4 -lnetcdf

grav_Part1_main.o: grav_Part1_main.cpp
	g++ -c -std=c++17 -O2 -Wall -o grav_Part1_main.o grav_Part1_main.cpp

grav_Part2_main.o: grav_Part2_main.cpp
	g++ -c -std=c++17 -O2 -Wall -o grav_Part2_main.o grav_Part2_main.cpp

grav_Part3_main.o: grav_Part3_main.cpp
	g++ -c -std=c++17 -O2 -Wall -o grav_Part3_main.o grav_Part3_main.cpp

grav_inter.o: grav_inter.cpp
	g++ -c -std=c++17 -O2 -Wall -o grav_inter.o grav_inter.cpp

grav_Part2_ex.o: grav_Part2_ex.cpp
	g++ -c -std=c++17 -O2 -Wall -o grav_Part2_ex.o grav_Part2_ex.cpp

grav_Part3_ex.o: grav_Part3_ex.cpp
	g++ -c -std=c++17 -O2 -Wall -o grav_Part3_ex.o grav_Part3_ex.cpp

clean:
	$(RM) *.o

.PHONY: all clean
