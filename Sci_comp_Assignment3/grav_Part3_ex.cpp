#include <stdio.h>
#include <iostream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>

struct Parameters {
    double mA, mB, mC, rB, wC;
};

double v_Eff (double r, void *params) {
    struct Parameters *p
    = (struct Parameters *) params;
    const double G = 6.7e-11;

    double mA = p->mA;
    double mB = p->mB;
    double mC = p->mC;
    double rB = p->rB;
    double wC = p->wC;

    double rBC = r-rB;
    
    double pot1 = -G*mA*mC/(r*abs(r));
    double pot2 = -G*mB*mC/(rBC*abs(rBC));
    double rot = (wC)*(wC)*r;
    return pot1 + pot2 +rot;
}

double find_root (double x_lo, double x_hi, Parameters &params) {
  int status;
  gsl_function F;

  int iter = 0, max_iter = 100;
  const gsl_root_fsolver_type *T;
  gsl_root_fsolver *s;

  double r = 0;
  
  F.function = &v_Eff;
  F.params = &params;

  T = gsl_root_fsolver_brent;
  s = gsl_root_fsolver_alloc (T);
  gsl_root_fsolver_set (s, &F, x_lo, x_hi);

  do
    {
      iter++;
      status = gsl_root_fsolver_iterate (s);
      r = gsl_root_fsolver_root (s);
      x_lo = gsl_root_fsolver_x_lower (s);
      x_hi = gsl_root_fsolver_x_upper (s);
      status = gsl_root_test_interval (x_lo, x_hi,
                                       0, 0.001);

      if (status == GSL_SUCCESS)
        printf ("Converged: \n");
    }
  while (status == GSL_CONTINUE && iter < max_iter);

  gsl_root_fsolver_free (s);

  return r;
}