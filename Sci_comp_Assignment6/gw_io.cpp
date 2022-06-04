#include <gw_io.h>

using namespace std;
using namespace netCDF;

string filename(int i) { // To get the filename from integers 
    string folder = "gwdata/"; // Everything is stored in gwdata/
    string filetype = ".nc";
    if (i == 0) {
        string name = "GWprediction"; // the zeroth is actually the prediction
        string fullname = folder + name + filetype;
        return fullname;
    } else if (i < 10) {
        string name = "detection0" + to_string(i); // First 8 have extra 0
        string fullname = folder + name + filetype;
        return fullname;
    }
    string name = "detection" + to_string(i);
    string fullname = folder + name + filetype;
    return fullname;
}



rvector<int> sort_indices(const rvector<double> A){ // Simple sorting algorithm, nothing fancy for 32 elements
    rvector<double> a = A.copy();

    rvector<int> indices(A.size());
    for(int i = 0; i<A.size(); i++){
        indices[i] = i;
    }
    
    for(int i = 0; i<A.size(); i++){
        for(int j = i+1; j<A.size(); j++){

            if (a[j]<a[i]){
                double temp_val = a[i];
                a[i] = a[j];
                a[j] = temp_val;

                int temp_ind = indices[i]; // the important part: we are only interested in the indices
                indices[i] = indices[j];
                indices[j] = temp_ind;
            }
        }
    }
    return indices;
}

void write_results(const rvector<int> sorted_ind, const rvector<double> coeffs){ // writing results to a txt 
    ofstream myfile;
    myfile.open("results.txt");
    for (int i = 0; i<5; i++){
        int ind = sorted_ind[32-i];
        myfile << filename(ind) << "\n";
        myfile << "CC: " << coeffs[ind] << "\n";
    }
    myfile.close();
}
