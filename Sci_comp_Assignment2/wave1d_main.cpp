//
// Based on wave1d.cpp by Ramses van Zon - 2015-2022
//
#include "wave1d_classheader.h"
#include "wave1d_io.h"
#include "wave1d_ex.h"

int main(int argc, char* argv[]){
    // Parameters
    Parameters params;

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
    int err = readAndAssign(argv[1], params);
    if (err == 3){
        return err;
    }

    // Define and allocate arrays
    rvector<double> rho_prev(params.npnts);
    rvector<double> rho(params.npnts);
    rvector<double> rho_next(params.npnts);

    rvector<double> x(params.npnts);
    rvector<double> t(params.noutTimes);

    // Initialize array of x values
    init_Xspace(x, params);
    init_Tspace(t, params);

    // Initialize wave with a triangle signal from xstart to xfinish
    init_TriangleIC(x, rho, rho_prev, params);

    // Initialize dataFile
    NcFile* dataFile = new NcFile(params.outfilename, NcFile::replace);

    // writes x and t to ncfile
    init_NetCDF(params, x, t, dataFile);

    //write the parameters as attributes
    write_Params_as_Att(params, dataFile);

    //write initial data
    dataFile -> getVar("rho").putVar({0, 0}, {(long unsigned int) params.ngrid, 1}, &rho[1]);
    // Take timesteps
    for (int s = 0; s < params.nsteps; s++) {

        // Set zero Dirichlet boundary conditions
        rho[0] = 0.0;
        rho[params.ngrid+1] = 0.0;

        // Evolve over a time dt
        step(rho, rho_prev, rho_next, params);

	    // Update values in arrays t+1 becomes the new t etc. 
        update_Arrays(rho, rho_prev, rho_next, s, params);

        // Write rho
        if ((s+1)%params.nper == 0){
            int i = (s+1)/params.nper;
            // writes to datafile
            dataFile -> getVar("rho").putVar({0, (long unsigned int) i}, {(long unsigned int) params.ngrid, 1}, &rho[1]);
        }
    }

    delete dataFile;
}
