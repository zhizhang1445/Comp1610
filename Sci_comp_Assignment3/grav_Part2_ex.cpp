#include <stdio.h>
#include <fstream>
#include "grav_class.h"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

int drdt_f (double t, const double r[], double drdt[], void *params){
  (void)(t); /* avoid unused parameter warning */
  Object obj = *(Object *)params;
  for (int i = 0 ; i < 3; i++){
    drdt[i] = obj.p[i]/obj.M;
  }
  return GSL_SUCCESS;
}

int dpdt_f (double t, const double p[], double dpdt[], void *params){
  (void)(t); /* avoid unused parameter warning */
  Object obj = *(Object *)params;
  for (int i = 0 ; i < 3; i++){
    dpdt[i] = obj.f[i];
  }
  return GSL_SUCCESS;
}

int check_Period( Object &obj, int P, int &nP, int n){
  double theta = atan2(obj.r[1], obj.r[0]);
  // std::cout << "Position: " << theta << std::endl;

  if (abs(theta) < 1e-3 && n > P+1e2){
    P = n;
    ++nP;
  }
  return P;
}

void write_Positions(double t, Object &objA, Object &objB, std::ofstream &fout){
  fout << t << " " << objA.r << " " << objB.r << "\n";
}