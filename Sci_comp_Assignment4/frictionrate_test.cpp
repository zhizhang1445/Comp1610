#include "friction.h"
#include "kinematics.h"
#include <iostream> 
#include <fstream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE frictionrate_test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(frictionrate_dt_test) {
    // input arrays:
    Parameters params(0.125, 10, 0, 9.8, 0.25, 0, 100);
    rvector<double> v = velocity(params);

    // function to check: 
    double res = frictionrate(params.dt, v);
    double diff = fabs(res-params.alpha);

    BOOST_CHECK(diff < 1e-5);
}

BOOST_AUTO_TEST_CASE(frictionrate_dv_test) {
    // input arrays:
    Parameters params(0.25, 10, 100, 1, 0.25, 0, 100);
    rvector<double> v = velocity(params);

    // function to check: 
    double res = frictionrate(params.dt, v);
    double diff = fabs(res-params.alpha);

    BOOST_CHECK(diff < 1e-5);
}