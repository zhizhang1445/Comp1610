#include "wave1d_classheader.h"
#include <iostream>
#include <rarray>
#include <fstream>
#include <filesystem>
#include <cmath>

void init_Xspace(rvector<double> x, Parameters params){
    for (int i = 0; i < params.npnts; i++) 
        x[i] = params.x1 + ((i-1)*(params.x2-params.x1))/params.ngrid; 
}

void init_Tspace(rvector<double> t, Parameters params){
    t[0] = 0;
    for (int s = 0; s < params.nsteps; s++){
        if ((s+1)%params.nper == 0){
            int i = (s+1)/params.nper;
            t[i] = s*params.dt;
        }
    }
        
}

void init_TriangleIC(rvector<double> x, rvector<double> rho, rvector<double> rho_prev, Parameters params){
    double xstart = 0.25*(params.x2 - params.x1) + params.x1;
    double xmid = 0.5*(params.x2 + params.x1);
    double xfinish = 0.75*(params.x2-params.x1) + params.x1;
    for (int i = 0; i < params.npnts; i++) {
        if (x[i] < xstart or x[i] > xfinish) {
            rho[i] = 0.0;
            // rho_withtime[i][0] = 0.0;
        }
        else {
            rho[i] = 0.25 - fabs(x[i]-xmid)/(params.x2-params.x1);
            // rho_withtime[i][0] = 0.25 - fabs(x[i]-xmid)/(params.x2-params.x1);
        }
        rho_prev[i] = rho[i];
    }
}

void step(rvector<double> rho, rvector<double> rho_prev, rvector<double> rho_next, Parameters params){
    for (int i = 1; i <= params.ngrid; i++) {
        double laplacian = pow(params.c/params.dx,2)*(rho[i+1] + rho[i-1] - 2*rho[i]);
        double friction = (rho[i] - rho_prev[i])/params.tau;
        rho_next[i] = 2*rho[i] - rho_prev[i] + params.dt*(laplacian*params.dt-friction);
    }
}

void update_Arrays(rvector<double> rho, rvector<double> rho_prev, rvector<double> rho_next, int s, Parameters params){
   	for (int i = 1; i <= params.ngrid; i++) {
            double temp = rho_prev[i];
            rho_prev[i] = rho[i];
            rho[i]      = rho_next[i];
            rho_next[i] = temp;
	} 
}