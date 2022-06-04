#include <gw_analysis.h>

using namespace std;

void fft_fast(const rvector<complex<double>>& f, rvector<complex<double>>& fhat, bool inverse) { // fft, taken from class powerpoint
    int n = f.size();
    fftw_plan p = fftw_plan_dft_1d(n, (fftw_complex*)f.data(), 
        (fftw_complex*)fhat.data(), inverse?FFTW_BACKWARD:FFTW_FORWARD,
        FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p); 
}

rvector<double> power_spec(const rvector<complex<double>>& f){ // Power Specturm calculation
    rvector<double> res(f.size());
    for (int i = 0; i< f.size(); i++){
        res[i] = real( f[i]*conj(f[i]) );
    }
    return res;
}

double dot_prod(const rvector<double>& F, const rvector<double>& G){ // Dot Product, to calculate Coefficients of correlation
    double res;

    for (int i = 0; i< F.size(); i++){
        res += F[i]*G[i];
    }
    return res;
}

double coeff_calc(const rvector<double>& F, const rvector<double>& G){ // Calculation of Correlation Coefficient
    double dotFG = dot_prod(F,G);
    double normF = dot_prod(F,F);
    double normG = dot_prod(G,G);

    double coeff = dotFG/(sqrt(normG*normF));
    return coeff;
}