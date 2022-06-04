#ifndef GW_ANALYSIS_H
#define GW_ANALYSIS_H

#include <complex>
#include <cmath>
#include <rarray>
#include <fftw3.h>

using namespace std;

void fft_fast(const rvector<complex<double>>& f, rvector<complex<double>>& fhat, bool inverse);

rvector<double> power_spec(const rvector<complex<double>>& f);

double dot_prod(const rvector<double>& F, const rvector<double>& G);

double coeff_calc(const rvector<double>& F, const rvector<double>& G);

#endif