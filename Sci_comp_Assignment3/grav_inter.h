#ifndef GRAV_INTER_H
#define GRAV_INTER_H

rvector<double> vec_diff(rvector<double> &x, rvector<double> &y);
rvector<double> vec_add(rvector<double> &x, rvector<double> &y);

double norm(rvector<double> &x);

double pot_2Newton(Object& params1, Object& params2);
rvector<double> f_2Newton(Object& params1, Object& params2);

double pot_nNewton(Object& params1, Object paramslist[], int nObj);
rvector<double> f_nNewton(Object& params1, Object paramslist[], int nObj);

#endif