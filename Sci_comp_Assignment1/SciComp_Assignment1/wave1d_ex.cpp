#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include "wave1d_header.h"



void init_Xspace(double x[], Parameters params){
    for (int i = 0; i < params.npnts; i++) 
        x[i] = params.x1 + ((i-1)*(params.x2-params.x1))/params.ngrid; 
}

void init_TriangleIC(double x[], double rho[], double rho_prev[], Parameters params){
    double xstart = 0.25*(params.x2 - params.x1) + params.x1;
    double xmid = 0.5*(params.x2 + params.x1);
    double xfinish = 0.75*(params.x2-params.x1) + params.x1;
    for (int i = 0; i < params.npnts; i++) {
        if (x[i] < xstart or x[i] > xfinish)
            rho[i] = 0.0;
        else
            rho[i] = 0.25 - fabs(x[i]-xmid)/(params.x2-params.x1);
        rho_prev[i] = rho[i];
    }    
}

void step(double rho[], double rho_prev[], double rho_next[], Parameters params){
    for (int i = 1; i <= params.ngrid; i++) {
        double laplacian = pow(params.c/params.dx,2)*(rho[i+1] + rho[i-1] - 2*rho[i]);
        double friction = (rho[i] - rho_prev[i])/params.tau;
        rho_next[i] = 2*rho[i] - rho_prev[i] + params.dt*(laplacian*params.dt-friction);
    }
}

void update_Arrays(double rho[], double rho_prev[], double rho_next[], Parameters params){
   	for (int i = 1; i <= params.ngrid; i++) {
            double temp = rho_prev[i];
            rho_prev[i] = rho[i];
            rho[i]      = rho_next[i];
            rho_next[i] = temp;
	} 
}