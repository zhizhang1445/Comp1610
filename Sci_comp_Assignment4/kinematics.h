#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <rarray>
#include <cmath>

struct Parameters{
    double alpha;
    double v0;
    double z0;
    double g;
    double dt;
    double t0;
    double tf;
    Parameters(double x1,double x2, double x3, double x4, double x5, double x6, double x7){
        alpha = x1;
        v0 = x2;
        z0 = x3;
        g = x4;
        dt = x5;
        t0 = x6;
        tf = x7;
    }
};

rvector<double> velocity(Parameters params);

rvector<double> position(Parameters params);

bool compare(rvector<double> x, rvector<double> y, double th);

#endif 