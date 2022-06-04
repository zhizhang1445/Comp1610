#ifndef WAVE1D_HEADER_H
#define WAVE1D_HEADER_H
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>

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
};

void init_Xspace(double x[], Parameters params);
void init_TriangleIC(double x[], double rho[], double rho_prev[], Parameters params);
void step(double rho[], double rho_prev[], double rho_next[], Parameters params);
void update_Arrays(double rho[], double rho_prev[], double rho_next[], Parameters params);

int readAndAssign(char* filename, Parameters& params);
void write_params(Parameters params, std::ofstream &fout);
void write_xandrho(double x[], double rho[], int s, Parameters params, std::ofstream &fout);

#endif