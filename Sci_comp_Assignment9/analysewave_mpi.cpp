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
#include <mpi.h>

int main(int argc, char* argv[])
{
    // check the command-line arguments
    if (argc != 3) {
        std::cerr << "Usage:\n"
                  << "  ./analysewave_mpi NETCDFFILENAME OUTPUTFILENAME\n"
                  << "Error: not enough command-line arguments.\n";
        return 1;
    } else if (not std::filesystem::exists(argv[1])) {
        std::cerr << "Usage:\n"
                  << "  ./analysewave_mpi NETCDFFILENAME OUTPUTFILENAME\n"
                  << "Error: NETCDFFILENAME " << argv[1] << " not found.\n";
        return 1;
    } else if (std::filesystem::exists(argv[2])) {
        std::cerr << "Usage:\n"
                  << "  ./analysewave_mpi NETCDFFILENAME OUTPUTFILENAME\n"
                  << "Warning: OUTPUTFILENAME (" << argv[2] << ") will be overwritten.\n";
        return 1;
    }

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

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
    
    // read one snapshot at a time
    rvector<double> snapshot(npoints);
    rvector<double> snapshotprev(npoints); // needed to compute time derivative

    rvector<double> globalmin((int)ntimes);
    rvector<double> globalmax((int)ntimes);
    rvector<double> globalsum((int)ntimes);
    rvector<double> globalenergy((int)ntimes);

    rvector<double> localmin((int)ntimes); localmin.fill(1.0e19);
    rvector<double> localmax((int)ntimes); localmax.fill(-1.0e19);
    rvector<double> localsum((int)ntimes); localsum.fill(0.0);
    rvector<double> localenergy((int)ntimes); localenergy.fill(0.0);

    int Nlocal = (npoints-1) / size;         // this may round down!
    int ibegin = rank * Nlocal;    // first index for this rank
    int iend = (rank+1) * Nlocal;  // end index for this rank, i.e., last index + 1
        // except if N is not divisable by size, adjust size of the last rank
    if (rank == size-1) {
        iend = npoints-1;
    }

    for (size_t t = 0; t < ntimes; t++) 
    {   
        // read a single snapshot
        rho.getVar({t,0}, {1,npoints}, snapshot);
        if (t==0) snapshotprev = snapshot.copy();

        for (int i = ibegin; i < iend; i++)
        {
            double cdrhodx = c*(snapshot[i+1] - snapshot[i])/dx;
            double drhodt = (snapshot[i] - snapshotprev[i])/dt;
            localenergy[t] += 0.5*(cdrhodx*cdrhodx + drhodt*drhodt);

            localsum[t] += snapshot[i];
	        if (localmin[t] > snapshot[i]) localmin[t] = snapshot[i];
	        if (localmax[t] < snapshot[i]) localmax[t] = snapshot[i];
        }
        localenergy[t] = localenergy[t]*dx; // energy is an integral, has common dx factor
        
        std::swap(snapshot, snapshotprev);
    }

    MPI_Allreduce(&localmin[0], &globalmin[0], ntimes, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&localmax[0], &globalmax[0], ntimes, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

    MPI_Allreduce(&localsum[0], &globalsum[0], ntimes, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&localenergy[0], &globalenergy[0], ntimes, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    if (rank == 0){ // Write everything
        std::ofstream outfile(argv[2]);

        for (size_t t = 0; t< ntimes; t++){
            double globalmean = globalsum[t]/(npoints-1);
            // output as text columns only rank 0
            outfile << t*dt << " " << globalmin[t] << " " << globalmean
                    << " " << globalmax[t]  << " " << globalenergy[t] << "\n";
        }
        outfile.close();
    }
    MPI_Finalize();
}
