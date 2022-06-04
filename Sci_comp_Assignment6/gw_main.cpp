#include <gw_analysis.h>
#include <gw_io.h>

using namespace std;
using namespace netCDF;

int main (void) {

    NcFile ncfile(filename(0), NcFile::read); // Read the data from GW_Prediction.nc
    rvector<complex<double>> gr(ncfile.getDim("nt").getSize()); // As shown from assignment doc
    ncfile.getVar("f").getVar(gr.data());

    rvector<complex<double>> ghat(gr.size()); // Allocation vector to store fourier transform
    fft_fast(gr, ghat, false); // Performing the DFT
    rvector<double> G_k = power_spec(ghat); // Finding the Power Spectrum

    rvector<double> coeffs(33); coeffs.fill(0.0); // Allocating the Array to store coefficients

    for (int i = 1; i<=32; i++){

        NcFile ncfile(filename(i), NcFile::read); // Reading detection files 
        rvector<complex<double>> fr(ncfile.getDim("nt").getSize());
        ncfile.getVar("f").getVar(fr.data());

        rvector<complex<double>> fhat(fr.size()); // Performing DFT and Power Spec. 
        fft_fast(fr, fhat, false);
        rvector<double> F_k = power_spec(fhat);
        coeffs[i] = coeff_calc(F_k, G_k); // Calculating Correlation Coefficients
    }
    rvector<int> sorted_ind = sort_indices(coeffs); // Sorting the Corrlation Coefficient
    write_results(sorted_ind, coeffs); // Writing the largest 5 on a txt file. 

    return 0;
}