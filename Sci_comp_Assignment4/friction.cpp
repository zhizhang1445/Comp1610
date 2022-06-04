#include "friction.h"
#include <rarray>
#include <cmath>

double frictionrate(double dt, const rvector<double>& x)
{
    double k = 0.0;
    for (int i = 0; i < x.size() - 2; i++) 
        k += (x[i+2] - x[i+1]) / (x[i+1] - x[i]);
    double averagek = k/(x.size() - 2);
    double alpha = -log(averagek)/dt;
    return alpha;
}

rvector<double> numdiff(double dt, const rvector<double>& x)
{
    rvector<double> result(x.size() - 1);
    for (int i = 0; i < result.size(); i++)
        result[i] = (x[i+1] - x[i]) / dt;
    return result;
}