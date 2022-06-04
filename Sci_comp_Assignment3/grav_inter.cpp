#include "grav_class.h"
#include <iostream>
#include <rarray>
#include <fstream>
#include <cmath>
// #include <filesystem>

rvector<double> vec_add(rvector<double> &x, rvector<double> &y){
    rvector<double> v_res(3);
    for (int i = 0; i<3; i++){
        v_res[i] = x[i]+y[i];
    }
    return v_res;
}
rvector<double> vec_diff(rvector<double> &x, rvector<double> &y){
    rvector<double> v_res(3);
    for (int i = 0; i<3; i++){
        v_res[i] = x[i]-y[i];
    }
    return v_res;
}

double norm(rvector<double> &x){
    double res = 0;
    for (int i = 0; i<3; i++){
        res += pow(x[i], 2);
    }
    res = sqrt(res);
    return res;
}

double pot_2Newton(Object& params1, Object& params2){
    const double G = 6.7e-11;

    rvector<double> r21 = vec_diff(params2.r, params1.r).copy();
    double dist = norm(r21);

    return -(G*params1.M*params2.M)/dist;
}

rvector<double> f_2Newton(Object& params2, Object& params1){ //Force exerted by obj2 onto obj1
    const double G = 6.7e-11;

    rvector<double> r21 = vec_diff(params2.r, params1.r).copy(); //Force is in the direction of obj2 relative to obj1
    double dist = norm(r21);
    double scalar = (G*params1.M*params2.M)/pow(dist, 3);
    rvector<double> f_res(3);

    for (int i = 0; i<3; i++){
        f_res[i] = scalar*r21[i];
    }
    return f_res;
}

double pot_nNewton(Object& params1, Object paramslist[], int nObj){
    double res_pot = 0;

    for (int i = 0; i<nObj; i++){
        res_pot += pot_2Newton(params1, paramslist[i]);
    }
    return res_pot;
}

rvector<double> f_nNewton(Object& params1, Object paramslist[], int nObj){
    rvector<double> v_res(3);
    v_res.fill(0.0);

    for (int i = 0; i<nObj; i++){
        rvector<double> v_temp = f_2Newton(params1, paramslist[i]);
        v_res = vec_add(v_res, v_temp).copy();
    }
    return v_res;
}



