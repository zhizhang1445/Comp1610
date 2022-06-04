#ifndef WAVE1D_CLASSHEADER_H
#define WAVE1D_CLASSHEADER_H
#include <iostream>

class Parameters{
    public:
        double  c;              // wave speed
        double  tau;            // damping time
        double  x1;             // left most x value
        double  x2;             // right most x value
        double  runtime;        // how long should the simulation try to compute?
        double  dx;             // spatial grid size
        double  outtime;        // how often should a snapshot of the wave be written out? 
        std::string outfilename;// name of the file with the output data

        int     ngrid;
        int     npnts;
        double  dt;    // time step size
        int     nsteps;  // number of steps of that size to reach runtime
        int     nper; 
        int     noutTimes; //number of time step to write out
};

#endif