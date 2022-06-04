#ifndef GRAV_PART2_EX_H
#define GRAV_PART2_EX_H

#include <stdio.h>
#include <fstream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

int drdt_f (double t, const double r[], double drdt[], void *params);

int dpdt_f (double t, const double p[], double dpdt[], void *params);

int check_Period( Object &obj, int P, int &nP, int n);

void write_Positions(double t, Object &objA, Object &objB, std::ofstream &fout);

#endif