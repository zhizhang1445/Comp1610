#ifndef GW_IO_H
#define GW_IO_H

#include <iostream>
#include <rarray>
#include <fstream>
#include <netcdf>
#include <gw_io.h>

using namespace std;
using namespace netCDF;

string filename(int i);

rvector<int> sort_indices(const rvector<double> A);

void write_results(const rvector<int> sorted_ind, const rvector<double> coeffs);

#endif