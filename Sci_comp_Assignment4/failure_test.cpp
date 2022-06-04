#include "friction.h"
#include "kinematics.h"
#include <iostream> 
#include <fstream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE failure_test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(failure_test) {
    // input arrays:
    Parameters params(11, 10, 0, 9.8, 0.25, 0, 100); //crank the friction up to 11
    rvector<double> v = velocity(params);

    // function to check: 
    double res = frictionrate(params.dt, v);
    double diff = fabs(res-params.alpha);

    BOOST_CHECK(diff >= 0); //would actually return true if res was a number
}