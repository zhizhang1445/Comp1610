# # makefile for the wave1d application
# makefile for the wave1d application

CXX=g++
CXXFLAGS=-std=c++17 -g -O2
LDFLAGS=-O2 -g
LDLIBS=-lnetcdf_c++4 -lnetcdf -lopenblas

all: wave1d wave1d_noOutput

# to build wave1d

OBJFILES=parameters.o output.o wavefields.o initialize.o ncoutput.o waveadvance.o

wave1d: wave1d.o $(OBJFILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

wave1d_noOutput: wave1d_noOutput.o $(OBJFILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

initialize.o: initialize.cpp initialize.h parameters.h
	$(CXX) -c $(CXXFLAGS) -o $@ $<
ncoutput.o: ncoutput.cpp ncoutput.h
	$(CXX) -c $(CXXFLAGS) -o $@ $<
output.o: output.cpp output.h
	$(CXX) -c $(CXXFLAGS) -o $@ $<
parameters.o: parameters.cpp parameters.h
	$(CXX) -c $(CXXFLAGS) -o $@ $<
wave1d.o: wave1d.cpp parameters.h output.h ncoutput.h wavefields.h waveadvance.h initialize.h
	$(CXX) -c $(CXXFLAGS) -o $@ $<
wave1d_noOutput.o: wave1d_noOutput.cpp parameters.h output.h ncoutput.h wavefields.h waveadvance.h initialize.h
	$(CXX) -c $(CXXFLAGS) -o $@ $<
waveadvance.o: waveadvance.cpp waveadvance.h parameters.h
	$(CXX) -c $(CXXFLAGS) -o $@ $<
wavefields.o: wavefields.cpp wavefields.h
	$(CXX) -c $(CXXFLAGS) -o $@ $<

# the rest is for integrated and unit tests

test: integratedtest runtestwavefields runtestparameters runtestwaveadvance runtestinitialize runtestoutput runtestncoutput

results.txt: wave1d waveparams.txt
	./$^
integratedtest: results.txt
	diff results.txt oldresults.txt

testwavefields.o: testwavefields.cpp wavefields.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
testwavefields: testwavefields.o wavefields.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) -lboost_unit_test_framework
runtestwavefields: testwavefields
	./testwavefields --log_level=all
testparameters.o: testparameters.cpp parameters.h maketestparameters.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
testparameters: testparameters.o parameters.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) -lboost_unit_test_framework
runtestparameters: testparameters
	./testparameters --log_level=all
testwaveadvance.o: testwaveadvance.cpp waveadvance.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
testwaveadvance: testwaveadvance.o waveadvance.o parameters.o wavefields.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) -lboost_unit_test_framework
runtestwaveadvance: testwaveadvance
	./testwaveadvance --log_level=all
testinitialize.o: testinitialize.cpp initialize.h maketestparameters.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
testinitialize: testinitialize.o initialize.o parameters.o wavefields.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) -lboost_unit_test_framework
runtestinitialize: testinitialize
	./testinitialize --log_level=all
testoutput.o: testoutput.cpp output.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
testoutput: testoutput.o output.o parameters.o wavefields.o maketestparameters.h
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) -lboost_unit_test_framework
runtestoutput: testoutput
	./testoutput --log_level=all
testncoutput.o: testncoutput.cpp ncoutput.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
testncoutput: testncoutput.o ncoutput.o parameters.o wavefields.o maketestparameters.h
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) -lboost_unit_test_framework
runtestncoutput: testncoutput
	./testncoutput --log_level=all

# customary clean rule(s):
clean:
	$(RM) $(OBJFILES)
	$(RM) test*.o

distclean: clean
	$(RM) wave1d results.txt testwavefields testparameters testinitialize testwaveadvance testoutput testncoutput

.PHONY: all clean test integratedtest distclean runtestwavefields runtestparameters runtestinitialize runtestwaveadvance runtestoutput runtestncoutput

