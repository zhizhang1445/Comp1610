//
// Based on wave1d.cpp by Ramses van Zon - 2015-2022
//
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cmath>
#include "wave1d_header.h"



int main(int argc, char* argv[]){
    // Parameters
    Parameters params;
    // std::cout << "print this if run" << ".\n";

    // Check command line argument
    if (argc != 2) {
        std::cerr << "Error: wave1d needs one parameter file argument.\n";
        return 1;
    }
    if (not std::filesystem::exists(argv[1])) {
        std::cerr << "Error: parameter file '" << argv[1] << "' not found.\n";
        return 2;
    }
    
    // Read the values from the parameter file specified on the command line,
    // initiate the parameter class and add derived parameters.
    readAndAssign(argv[1], params);
    // std::cout << params.npnts << ".\n";

    // Define and allocate arrays
    double* rho_prev = new double[params.npnts]{0}; // time step t-1
    double* rho      = new double[params.npnts]{0}; // time step t
    double* rho_next = new double[params.npnts]{0}; // time step t+1
    double* x        = new double[params.npnts]{0}; // x values
    // std::cout << "print this if array" << ".\n";

    // Initialize array of x values
    init_Xspace(x, params);

    // Initialize wave with a triangle signal from xstart to xfinish
    init_TriangleIC(x, rho, rho_prev, params);

    // open the result file and start writint parameters
    std::ofstream fout(params.outfilename);
    write_params(params, fout);
    write_xandrho(x, rho, 0, params, fout);

    // Take timesteps
    for (int s = 0; s < params.nsteps; s++) {

        // Set zero Dirichlet boundary conditions
        rho[0] = 0.0;
        rho[params.ngrid+1] = 0.0;

        // Evolve over a time dt
        step(rho, rho_prev, rho_next, params);

	// Update values in arrays t+1 becomes the new t etc. 
    update_Arrays(rho, rho_prev, rho_next, params);

        if ((s+1)%params.nper == 0) {
            write_xandrho(x, rho, s, params, fout);
        }
    }

    fout.close();
    std::cout << "Results written to '"<< params.outfilename << "'.\n"; 
    
    // Deallocate memory
    delete[] rho_prev;
    delete[] rho;
    delete[] rho_next;
    delete[] x;
}
