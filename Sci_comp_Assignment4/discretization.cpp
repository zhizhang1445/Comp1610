#include "friction.h"
#include "kinematics.h"
#include <iostream> 
#include <fstream>

int main(){
    double dt0 = pow(2,-7);
    double t0 = 0;
    double tf = 100;
    int npow_dt = 21;

    Parameters params(1.25e-5, 10, 0, 9.8, dt0, t0, tf);
    std::ofstream fout("discretization_results.txt");
    fout << "dt  " << "estimated alpha   " << "absolute error" << "\n";
    printf ("%.30s %.30s %.30s\n", "     dt    ", "  est alpha  ", "   err   ");

    for(int i = 0; i < npow_dt; i++){
        rvector<double> z = position(params);
        // std::cout << z.size() << std::endl;
        double rate = frictionrate(params.dt, numdiff(params.dt, z));

        fout << params.dt << " " << rate << " " << fabs(rate-params.alpha) << "\n";

        // std::cout << params.dt << " " << rate << " " << rate2 << "\n";
        // std::cout << params.dt << " " << rate << " " << fabs(rate-params.alpha) << "\n";
        printf ("%.9f %.9f %.9f\n", params.dt, rate, fabs(rate-params.alpha));

        params.dt = sqrt(2)*params.dt;
    }

}

// int main(){
//     // double dt0 = pow(2, 0);
//     double dt0 = 0.9;
//     double t0 = 0;
//     double tf = 1000;
//     int n_dt = 20;

//     Parameters params(1.25e-2, 10, 0, 9.8, dt0, t0, tf);
//     std::ofstream fout("discretization_results.txt");
//     fout << "dt  " << "estimated alpha   " << "absolute error" << "\n";
//     printf ("%.30s %.30s %.30s\n", "     dt    ", "  est alpha  ", "   err   ");

//     for(int i = 0; i < n_dt; i++){
//         params.dt = (i+1)*(12.5);
//         // params.dt = (i+1)*(2.5) + dt0;

//         rvector<double> z = position(params);
//         // std::cout << z.size() << std::endl;
//         double rate = frictionrate(params.dt, numdiff(params.dt, z));

//         fout << params.dt << " " << rate << " " << fabs(rate-params.alpha) << "\n";

//         // std::cout << params.dt << " " << rate << " " << rate2 << "\n";
//         // std::cout << params.dt << " " << rate << " " << fabs(rate-params.alpha) << "\n";
//         printf ("%.9f %.9f %.9f\n", params.dt, rate, fabs(rate-params.alpha));
//     }
// }