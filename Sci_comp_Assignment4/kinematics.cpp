#include "kinematics.h"

rvector<double> velocity(Parameters params) {
    int npoints = ((params.tf - params.t0)/params.dt) +1; // +1 for initial condition
    // std::cout << "npt vel:" << npoints << std::endl;
    rvector<double> results(npoints);
    double net_a = params.g/params.alpha;

    for (int i = 0; i < npoints; i++){
        double t = i*params.dt+params.t0;
        results[i] = (params.v0 + net_a)*exp(-1*params.alpha*t) - net_a;
    }

    return results;
}

rvector<double> position(Parameters params) {
    int npoints = ((params.tf - params.t0)/params.dt ) +1; // +1 for initial condition
    rvector<double> results(npoints);
    double net_a = params.g/params.alpha;

    for (int i = 0; i < npoints; i++){
        double t = i*params.dt+params.t0;
        results[i] = (params.v0 + net_a)*(1-exp(-1*params.alpha*t))/params.alpha;
        results[i] += params.z0;
        results[i] -= net_a*t;
    }
    return results;
}

bool compare(rvector<double> x, rvector<double> y, double th){
    if (x.size() == y.size()){
        for(int i =0; i<x.size(); i++){
            double diff = fabs(x[i]-y[i]);

            if (diff > th){
                return false;
            }
        }
        return true;
    }
    std::cout << "size not equal" << std::endl;
    return false;
}