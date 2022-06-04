#ifndef WAVE1D_EX_H
#define WAVE1D_EX_H
// #include <iostream>
#include <rarray>
#include <cmath>

void init_Xspace(rvector<double> x, Parameters params);
void init_Tspace(rvector<double> t, Parameters params);

void init_TriangleIC(rvector<double> x, rvector<double> rho, rvector<double> rho_prev, Parameters params);
void step(rvector<double> rho, rvector<double> rho_prev, rvector<double> rho_next, Parameters params);
void update_Arrays(rvector<double> rho, rvector<double> rho_prev, rvector<double> rho_next, int s, Parameters params);

#endif
