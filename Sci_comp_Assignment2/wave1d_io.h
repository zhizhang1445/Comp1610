#ifndef WAVE1D_IO_H
#define WAVE1D_IO_H
#include <rarray>
#include <filesystem>
#include <netcdf>
using namespace netCDF;

int readAndAssign(char* filename, Parameters& params);

// void write_params(Parameters params, std::ofstream &fout);
void write_Params_as_Att(Parameters params, NcFile* dataFile);

// void write_xandrho2txt(rvector<double> x, rvector<double> rho, int s, Parameters params, std::ofstream &fout);
// void write_rho(rvector<double> rho, int s, NcVar& data, Parameters params);
void init_NetCDF(Parameters params, rvector<double> x, rvector<double> t, NcFile* dataFile);
#endif
