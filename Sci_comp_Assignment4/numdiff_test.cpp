#include "friction.h"
#include "kinematics.h"
#include <iostream> 
#include <fstream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE numdiff_test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(numdiff_new_test) {
    // input arrays:
    Parameters params1(0.25, 10, 0, 9.8, 0.25, 0, 100);
    rvector<double> z = position(params1);
    Parameters params2(0.25, 10, 0, 9.8, 0.25, 0.125, 100-0.125); // Numdiff is a finite element so technically computes at timesteps inbetween. 
    rvector<double> v = velocity(params2);

    // function to check: 
    rvector<double> res = numdiff(params1.dt, z);

    BOOST_CHECK(compare(res, v, 0.01));
}

BOOST_AUTO_TEST_CASE(numdiff_req_test) {
    // input arrays:
    Parameters params1(0.125, 10, 0, 9.8, 0.25, 0, 100);
    rvector<double> z = position(params1);
    Parameters params2(0.125, 10, 0, 9.8, 0.25, 0.125, 100-0.125);
    rvector<double> v = velocity(params2);

    // function to check:
    rvector<double> res = numdiff(params1.dt, z);
    // std::cout << z.size() << std::endl; 
    // std::cout << v.size() << std::endl; 

    BOOST_CHECK(compare(res, v, 0.01));
}