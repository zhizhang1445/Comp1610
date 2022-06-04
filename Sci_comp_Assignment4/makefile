CXX=g++ 
CXXFLAGS=-std=c++17 -O2 -Wall
RFLAGS=--log_level=all

all: frictionrate_test numdiff_test failure_test discretization

test: frictionrate_test numdiff_test failure_test
	./frictionrate_test ${RFLAGS}
	./numdiff_test ${RFLAGS}
	./failure_test ${RFLAGS}

FRICTIONRATETEST: frictionrate_test
	./frictionrate_test ${RFLAGS}

NUMDIFFTEST: numdiff_test
	./numdiff_test ${RFLAGS}

FAILURETEST: failure_test
	./failure_test ${RFLAGS}

discretization: discretization.o friction.o kinematics.o
	${CXX} ${CXXFLAGS} -o discretization friction.o discretization.o kinematics.o

frictionrate_test: friction.o frictionrate_test.o kinematics.o
	${CXX} ${CXXFLAGS} -o frictionrate_test friction.o frictionrate_test.o kinematics.o -lboost_unit_test_framework

numdiff_test: friction.o numdiff_test.o kinematics.o
	${CXX} ${CXXFLAGS} -o numdiff_test friction.o numdiff_test.o kinematics.o -lboost_unit_test_framework

failure_test: friction.o failure_test.o kinematics.o
	${CXX} ${CXXFLAGS} -o failure_test friction.o failure_test.o kinematics.o -lboost_unit_test_framework

kinematics.o: kinematics.cpp
	${CXX} ${CXXFLAGS} -c -o kinematics.o kinematics.cpp

friction.o: friction.cpp
	${CXX} ${CXXFLAGS} -c -o friction.o friction.cpp

frictionrate_test.o: frictionrate_test.cpp
	${CXX} ${CXXFLAGS} -c -o frictionrate_test.o frictionrate_test.cpp

numdiff_test.o: numdiff_test.cpp
	${CXX} ${CXXFLAGS} -c -o numdiff_test.o numdiff_test.cpp 

failure_test.o: failure_test.cpp
	${CXX} ${CXXFLAGS} -c -o failure_test.o failure_test.cpp

discretization.o: discretization.cpp
	${CXX} ${CXXFLAGS} -c -o discretization.o discretization.cpp   

clean:
	${RM} *.o

.PHONY: all clean
