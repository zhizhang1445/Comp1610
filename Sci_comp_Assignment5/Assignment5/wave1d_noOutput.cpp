/// @file wave1d.cc
/// @brief Simulates a one-dimensional damped wave equation
/// @author Ramses van Zon
/// @date 2015-2022

#include <iostream>
#include <fstream>
#include <cmath>
#include "parameters.h"
#include "output.h"
#include "ncoutput.h"
#include "wavefields.h"
#include "waveadvance.h"
#include "initialize.h"

int main(int argc, char* argv[])
{
    // Parameters
    InputParameters params;
    
    // Check command line argument
    if (argc != 2) {
        std::cerr << "Error: wave1d needs one parameter file argument.\n";
        return 1;
    }

    params = read_parameters(argv[1]);

    // Derived parameters
    DerivedParameters derivs = derived_parameters(params);
    
    // Allocate arrays
    WaveFields w = allocate_wave_arrays(derivs.ngrid, params.x1, params.x2);
    
    // Initialize position array and wave fields
    triangle_wave(w);

    rmatrix<double> G(derivs.npnts, derivs.npnts); G.fill(0.0);
    
    for (int i = 0; i < derivs.npnts; i++) {
        G[i][i] = 1.0;
        if (i > 0 && i < (derivs.npnts-1)) {
            G[i][i-1] = G[i][i+1] = 1;
            G[i][i] = - 2.0;
        }
    }
    
    rmatrix<double> G_band(derivs.npnts, 3);
    for (int i = 1; i< derivs.npnts-1; i ++){
        G_band[i][1] = -2.0;
        G_band[i][0] = G_band[i][2] = 1.0;
    }
    G_band[0][1] = G_band[derivs.npnts-1][1] = -2.0;
    G_band[0][2] = 1.0;
    G_band[derivs.npnts-1][1] = 1.0;

    // Take timesteps
    for (int s = 0; s < derivs.nsteps; s++) {       
        // Evolve one time step
        advance_wave_dgemv(w, params, derivs, G);
    }
    
    // Deallocate memory
    deallocate_wave_arrays(w);
}