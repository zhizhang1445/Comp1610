/// @file waveadvance.cpp
/// @brief Module to advance the 1d wave one time step - see waveadvance.h for more information.
/// @author Ramses van Zon
/// @date March 6, 2022

#include "waveadvance.h"
#include <cmath>

void advance_wave(WaveFields& w,
                  const InputParameters& params,
                  const DerivedParameters& derivs)
{
     // Set zero Dirichlet boundary conditions
     w.rho[0] = 0.0;
     w.rho[derivs.ngrid+1] = 0.0;

     // Evolve over a time dt
     #pragma omp parallel default(none) shared(derivs, w, params)
     
     #pragma omp for
     for (int i = 1; i <= derivs.ngrid; i++) {
         double laplacian = pow(params.c/params.dx,2)*(w.rho[i+1] + w.rho[i-1] - 2*w.rho[i]);
         double friction = (w.rho[i] - w.rho_prev[i])/params.tau;
         w.rho_next[i] = 2*w.rho[i] - w.rho_prev[i] + derivs.dt*(laplacian*derivs.dt-friction);
     }
     // Update values in arrays t+1 becomes the new t etc.
     #pragma omp for
     for (int i = 1; i <= derivs.ngrid; i++) {
         double temp = w.rho_prev[i];
         w.rho_prev[i] = w.rho[i];
         w.rho[i]      = w.rho_next[i];
         w.rho_next[i] = temp;
     }
}   