#include "wave1d_classheader.h"
#include <iostream>
#include <rarray>
#include <fstream>
#include <filesystem>
// #include <cmath>
#include <netcdf> 
using namespace netCDF;

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
        params.noutTimes = (params.nsteps/params.nper) + 1; // number of times t is written (+1 for initial condition)
        return 0;
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "Error while reading file '" << filename << "'.\n";
        return 3;
    } 
}

void write_Params_as_Att(Parameters params, NcFile* dataFile){
    // Report all the parameters to attributes in the output file
    dataFile -> putAtt("c:", ncDouble, params.c);
    dataFile -> putAtt("tau:", ncDouble, params.tau); 
    dataFile -> putAtt("x1:", ncDouble, params.x1);
    dataFile -> putAtt("x2:", ncDouble, params.x2);
    dataFile -> putAtt("runtime:", ncDouble, params.runtime);
    dataFile -> putAtt("dx:", ncDouble, params.dx);
    dataFile -> putAtt("outtime:", ncDouble, params.outtime);
    dataFile -> putAtt("ngrid:", ncDouble, params.ngrid);
    dataFile -> putAtt("dt:", ncDouble, params.dt);
    dataFile -> putAtt("nsteps:", ncDouble, params.nsteps);
    dataFile -> putAtt("nper:", ncDouble, params.nper);
}
i
void init_NetCDF(Parameters params, rvector<double> x, rvector<double> t, NcFile* dataFile){
    // Report all the parameters to attributes in the output file
    NcDim tDim = dataFile->addDim("t", params.noutTimes);
    NcDim xDim = dataFile->addDim("x", params.ngrid);

    NcVar data1 = dataFile->addVar("t", ncDouble, {tDim});
    data1.putVar(&t[0]);

    NcVar data2 = dataFile->addVar("x", ncDouble, {xDim});
    data2.putVar(&x[1]);

    NcVar data3 = dataFile->addVar("rho", ncDouble, {xDim, tDim}); 
}

// void write_params(Parameters params, std::ofstream &fout){
//     // Report all the parameters in the output file
//     fout << "#c       " << params.c       << "\n";
//     fout << "#tau     " << params.tau     << "\n";
//     fout << "#x1      " << params.x1      << "\n";
//     fout << "#x2      " << params.x2      << "\n";
//     fout << "#runtime " << params.runtime << "\n";
//     fout << "#dx      " << params.dx      << "\n";
//     fout << "#outtime " << params.outtime << "\n"; 
//     fout << "#ngrid   " << params.ngrid   << "\n";
//     fout << "#dt      " << params.dt      << "\n";
//     fout << "#nsteps  " << params.nsteps  << "\n";    
//     fout << "#nper    " << params.nper    << "\n";
// }


// void write_xandrho2txt(rvector<double> x, rvector<double> rho, int s, Parameters params, std::ofstream &fout){
//     // Output initial wave signal to file
//     fout << "\n\n# t = " << s*params.dt << "\n";
//     for (int i = 1; i <= params.ngrid; i++) {
//         fout << x[i] << " " << rho[i] << "\n";
//     }
// }

