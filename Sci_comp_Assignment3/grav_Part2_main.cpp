#include "grav_class.h"
#include "grav_inter.h"
#include "grav_Part2_ex.h"


int main(void){
    double rA[3] = {0, 0, 0};
    double rB[3] = {1.48e11, 0, 0};
    double pA[3] = {0, 0, 0};
    double pB[3] = {0, 6e24*3e4, 0};
    // rvector<double> y(buf, 3);
    // rvector<double> z({1, 0, 0});

    // std::cout << y <<std::endl;
    Object objA(2e30, rA, pA);
    Object objB(6e24, rB, pB);

    gsl_odeiv2_system sys_rA = {drdt_f, nullptr, 3, &objA};
    gsl_odeiv2_system sys_pA = {dpdt_f, nullptr, 3, &objA};
    gsl_odeiv2_system sys_rB = {drdt_f, nullptr, 3, &objB};
    gsl_odeiv2_system sys_pB = {dpdt_f, nullptr, 3, &objB};

    // gsl_odeiv2_driver * d_r = gsl_odeiv2_driver_alloc_y_new (&sys_r, gsl_odeiv2_step_rk8pd, 1, 1e-6, 0.0);
    gsl_odeiv2_driver * d_rA = gsl_odeiv2_driver_alloc_y_new (&sys_rA, gsl_odeiv2_step_rk8pd, 1e3, 1e3, 0.01);
    gsl_odeiv2_driver * d_pA = gsl_odeiv2_driver_alloc_y_new (&sys_pA, gsl_odeiv2_step_rk8pd, 1e3, 1e3, 0.01);
    gsl_odeiv2_driver * d_rB = gsl_odeiv2_driver_alloc_y_new (&sys_rB, gsl_odeiv2_step_rk8pd, 1e3, 1e3, 0.01);
    gsl_odeiv2_driver * d_pB = gsl_odeiv2_driver_alloc_y_new (&sys_pB, gsl_odeiv2_step_rk8pd, 1e3, 1e3, 0.01);

    double t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    double tf = 1e8;
    int nsteps = 1e5;

    double P = 0;
    int nP = 0;

    std::ofstream fout("Results.txt");
    fout << "Time (s):    " << "Position of A (m):     " << "Position of B (m):     " << "\n";

    for(int n = 0; n<nsteps; n++){
      
      double ti = n*tf/nsteps;

      int status = gsl_odeiv2_driver_apply (d_rA, &t1, ti, objA.r);
      objA.f = f_2Newton(objB, objA);
      status = status * gsl_odeiv2_driver_apply (d_pA, &t2, ti, objA.p);

      status = status * gsl_odeiv2_driver_apply (d_rB, &t3, ti, objB.r);
      objB.f = f_2Newton(objA, objB);
      status = status * gsl_odeiv2_driver_apply (d_pB, &t4, ti, objB.p);


      if (status != GSL_SUCCESS){
        printf ("error, return value=%d\n", status);
        break;
      }

      P = check_Period(objB, P, nP, n);
      write_Positions(t1, objA, objB, fout);

    }
    fout << "\n" << "Period: " << P*tf/(nsteps*nP) << "\n";
    std::cout << "Period: " << P*tf/(nsteps*nP) << std::endl;
    fout.close();
    return 0;
}