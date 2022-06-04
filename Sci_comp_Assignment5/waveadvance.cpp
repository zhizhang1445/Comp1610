/// @file waveadvance.cpp
/// @brief Module to advance the 1d wave one time step - see waveadvance.h for more information.
/// @author Ramses van Zon
/// @date March 6, 2022

#include "waveadvance.h"
#include <cmath>
#include <cblas.h>

void advance_wave(WaveFields& w,
                  const InputParameters& params,
                  const DerivedParameters& derivs)
{
     // Set zero Dirichlet boundary conditions
     w.rho[0] = 0.0;
     w.rho[derivs.ngrid+1] = 0.0;
     // Evolve over a time dt
     for (int i = 1; i <= derivs.ngrid; i++) {
         double laplacian = pow(params.c/params.dx,2)*(w.rho[i+1] + w.rho[i-1] - 2*w.rho[i]);
         double friction = (w.rho[i] - w.rho_prev[i])/params.tau;
         w.rho_next[i] = 2*w.rho[i] - w.rho_prev[i] + derivs.dt*(laplacian*derivs.dt-friction);
     }
     // Update values in arrays t+1 becomes the new t etc.
     for (int i = 1; i <= derivs.ngrid; i++) {
         double temp = w.rho_prev[i];
         w.rho_prev[i] = w.rho[i];
         w.rho[i]      = w.rho_next[i];
         w.rho_next[i] = temp;
     }
}

void advance_wave_dgemv(WaveFields& w,
                  const InputParameters& params,
                  const DerivedParameters& derivs,
                  rmatrix<double> G)
{
     // Set zero Dirichlet boundary conditions
     w.rho[0] = 0.0;
     w.rho[derivs.ngrid+1] = 0.0;

     // Evolve over a time dt
     double alpha = pow(params.c/params.dx,2);

     rvector<double> laplacian(derivs.npnts); laplacian.fill(0.0);

     cblas_dgemv(CblasRowMajor, CblasNoTrans, derivs.npnts, derivs.npnts, 
        alpha, G.data(), derivs.npnts, w.rho.data(), 1, 0.0, 
        laplacian.data(), 1);

     for (int i = 1; i <= derivs.ngrid; i++) {
         double friction = (w.rho[i] - w.rho_prev[i])/params.tau;
         w.rho_next[i] = 2*w.rho[i] - w.rho_prev[i] + derivs.dt*(laplacian[i]*derivs.dt-friction);
     }
     // Update values in arrays t+1 becomes the new t etc.
     for (int i = 1; i <= derivs.ngrid; i++) {
         double temp = w.rho_prev[i];
         w.rho_prev[i] = w.rho[i];
         w.rho[i]      = w.rho_next[i];
         w.rho_next[i] = temp;
     }
}  

void advance_wave_dgbmv(WaveFields& w,
                  const InputParameters& params,
                  const DerivedParameters& derivs,
                  rmatrix<double> G_band)
{
     // Set zero Dirichlet boundary conditions
     w.rho[0] = 0.0;
     w.rho[derivs.ngrid+1] = 0.0;

     // Evolve over a time dt
     

     rvector<double> laplacian(derivs.npnts); laplacian.fill(0.0);
     double alpha = pow(params.c/params.dx,2);
    //  std::cout << G.extent(0) << G.extent(1) << std::endl;

     cblas_dgbmv(CblasColMajor, CblasNoTrans, derivs.npnts, 
        derivs.npnts, 1, 1, alpha, G_band.data(), 3, 
        w.rho.data(), 1, 0.0, laplacian.data(), 1);

     for (int i = 1; i <= derivs.ngrid; i++) {
         double friction = (w.rho[i] - w.rho_prev[i])/params.tau;
         w.rho_next[i] = 2*w.rho[i] - w.rho_prev[i] + derivs.dt*(laplacian[i]*derivs.dt-friction);
     }
     // Update values in arrays t+1 becomes the new t etc.
     for (int i = 1; i <= derivs.ngrid; i++) {
         double temp = w.rho_prev[i];
         w.rho_prev[i] = w.rho[i];
         w.rho[i]      = w.rho_next[i];
         w.rho_next[i] = temp;
     }
}  