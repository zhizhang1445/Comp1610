#ifndef FRICTIONH
#define FRICTIONH

#include <rarray>

double frictionrate(double dt, const rvector<double>& v);
rvector<double> numdiff(double dt, const rvector<double>& z);

#endif