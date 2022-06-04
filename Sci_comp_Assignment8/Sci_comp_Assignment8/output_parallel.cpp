/// @file output.cpp
/// @brief ascii output module - see output.h for more information.
/// @author Ramses van Zon
/// @date March 6, 2022

#include "output.h"
#include <sstream>

// start writing output 
void output_start(const InputParameters& p,
                  const DerivedParameters & d,
                  std::ofstream& fout)
{
    // Open output file
    fout.open(p.outfilename);
    
    // Report all the parameters in the output file
    fout << "#c       " << p.c       << "\n";
    fout << "#tau     " << p.tau     << "\n";
    fout << "#x1      " << p.x1      << "\n";
    fout << "#x2      " << p.x2      << "\n";
    fout << "#runtime " << p.runtime << "\n";
    fout << "#dx      " << p.dx      << "\n";
    fout << "#outtime " << p.outtime << "\n"; 
    fout << "#ngrid   " << d.ngrid   << "\n";
    fout << "#dt      " << d.dt      << "\n";
    fout << "#nsteps  " << d.nsteps  << "\n";    
    fout << "#nper    " << d.nper    << "\n";
}

// output a snapshot
void output_snapshot(double t, const WaveFields& wf, std::ofstream& fout)
{
    std::string temp[wf.x.size()];

    #pragma omp parallel for default(none) shared(t, wf, fout, temp)    
    for (int i = 1; i <= wf.x.size()-2; i++) {
        std::stringstream ss;
        ss << wf.x[i] << " " << wf.rho[i];
        temp[i] = ss.str();
        // temp[i] =  std::to_string(wf.x[i]) + " " + std::to_string(wf.rho[i]);
    }
    
    // #pragma omp single
    fout << "\n\n# t = " << t << "\n";
    // #pragma omp for
    for (int i = 1; i <= wf.x.size()-2; i++) {
        //#pragma omp critical
        // std::cout << temp[i] << "\n";
        fout << temp[i] << "\n";
    }
}

// stop writing output
void output_finalize(std::ofstream& fout)
{
    fout.close();
}