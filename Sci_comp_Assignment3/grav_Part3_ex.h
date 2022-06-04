#ifndef GRAV_PART3_EX_H
#define GRAV_PART3_EX_H

#include <stdio.h>
#include <iostream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <fstream>

struct Parameters {
    double mA, mB, mC, rB, wC;
};

double v_Eff (double r, void *params);

double find_root (double x_lo, double x_hi, Parameters &params);

#endif