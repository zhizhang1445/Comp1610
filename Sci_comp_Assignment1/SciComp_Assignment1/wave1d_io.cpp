#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include "wave1d_header.h"

int readAndAssign(char* filename, Parameters& params){
    std::ifstream infile(filename);
    infile.exceptions(std::ifstream::failbit|std::ifstream::badbit); 
    try {
        infile >> params.c;
        infile >> params.tau;
        infile >> params.x1;
        infile >> params.x2;
        infile >> params.runtime;
        infile >> params.dx;
        infile >> params.outtime;
        infile >> params.outfilename;
        infile.close();

        params.ngrid   = (params.x2-params.x1)/params.dx;  // number of x points
        params.npnts   = params.ngrid + 2;   // number of x points including boundary points
        params.dt      = 0.5*params.dx/params.c;    // time step size
        params.nsteps  = params.runtime/params.dt;  // number of steps of that size to reach runtime
        params.nper    = params.outtime/params.dt;

        return 0;
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "Error while reading file '" << filename << "'.\n";
        return 3;
    } 
}

void write_params(Parameters params, std::ofstream &fout){
    // Report all the parameters in the output file
    fout << "#c       " << params.c       << "\n";
    fout << "#tau     " << params.tau     << "\n";
    fout << "#x1      " << params.x1      << "\n";
    fout << "#x2      " << params.x2      << "\n";
    fout << "#runtime " << params.runtime << "\n";
    fout << "#dx      " << params.dx      << "\n";
    fout << "#outtime " << params.outtime << "\n"; 
    fout << "#ngrid   " << params.ngrid   << "\n";
    fout << "#dt      " << params.dt      << "\n";
    fout << "#nsteps  " << params.nsteps  << "\n";    
    fout << "#nper    " << params.nper    << "\n";
}

void write_xandrho(double x[], double rho[], int s, Parameters params, std::ofstream &fout){
    // Output initial wave signal to file
    fout << "\n\n# t = " << s*params.dt << "\n";
    for (int i = 1; i <= params.ngrid; i++) {
        fout << x[i] << " " << rho[i] << "\n";
    }
}