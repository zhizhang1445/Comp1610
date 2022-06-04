//
// analysewave.cpp - analyse a netcdf file produced by wave1d
//                   produces a time series of the energy, and the
//                   minimum, mean, and maximum of the wave form.
//
// Usage:
//  ./analysewave NETCDFFILENAME OUTPUTFILENAME
//
// For assignment 9 of PHY1610 (Scientific Computing), Winter 2022
//
// PS: The wave energy is E = \int dx ([d\rho/dt]^2 + c^2 [d\rho/dx]^2)/2.
//

#include <netcdf>
#include <rarray>
#include <fstream>
#include <filesystem>

int main(int argc, char* argv[])
{
    // check the command-line arguments
    if (argc != 3) {
        std::cerr << "Usage:\n"
                  << "  ./analysewave NETCDFFILENAME OUTPUTFILENAME\n"
                  << "Error: not enough command-line arguments.\n";
        return 1;
    } else if (not std::filesystem::exists(argv[1])) {
        std::cerr << "Usage:\n"
                  << "  ./analysewave NETCDFFILENAME OUTPUTFILENAME\n"
                  << "Error: NETCDFFILENAME " << argv[1] << " not found.\n";
        return 1;
    } else if (std::filesystem::exists(argv[2])) {
        std::cerr << "Usage:\n"
                  << "  ./analysewave NETCDFFILENAME OUTPUTFILENAME\n"
                  << "Warning: OUTPUTFILENAME (" << argv[2] << ") will be overwritten.\n";
        return 1;
    }

    // open netcdf file and find the attributes and rho variable
    netCDF::NcFile ncf(argv[1], netCDF::NcFile::read);
    netCDF::NcVar rho = ncf.getVar("rho");
    size_t ntimes = rho.getDim(0).getSize();
    size_t npoints = rho.getDim(1).getSize();
    double dt, dx, c;
    int nper;
    ncf.getAtt("nper").getValues(&nper);
    ncf.getAtt("dt").getValues(&dt);
    ncf.getAtt("dx").getValues(&dx);
    ncf.getAtt("c").getValues(&c);
    dt *= nper;  // actual time between snapshots

    // write results of analysis to a file
    std::ofstream outfile(argv[2]);
    
    // read one snapshot at a time
    rvector<double> snapshot(npoints);
    rvector<double> snapshotprev(npoints); // needed to compute time derivative
    
    for (size_t t = 0; t < ntimes; t++) 
    {   
        // read a single snapshot
        rho.getVar({t,0}, {1,npoints}, snapshot);
        if (t==0) snapshotprev = snapshot.copy();

	// accumulate energy, sum, min and mean of the wave
        double energy = 0.0;
        double sum = 0.0;
	    double min = +1.0e9;
	    double max = -1.0e9;


        for (int i = 0; i < snapshot.size()-1; i++)
        {
            double cdrhodx = c*(snapshot[i+1] - snapshot[i])/dx;
            double drhodt = (snapshot[i] - snapshotprev[i])/dt;
            energy += 0.5*(cdrhodx*cdrhodx + drhodt*drhodt);
            sum += snapshot[i];
	        if (min > snapshot[i]) min = snapshot[i];
	        if (max < snapshot[i]) max = snapshot[i];
        }
        energy = energy*dx; // energy is an integral, has common dx factor
        double mean = sum/(npoints-1); // get mean from sum

	// output as text columns
        outfile << t*dt << " " << min << " " << mean
                << " " << max  << " " << energy << "\n";

	// store this snapshot as the next previous snapshot without a copy
        std::swap(snapshot, snapshotprev);
    }
    
    outfile.close();
}
