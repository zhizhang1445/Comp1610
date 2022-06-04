#include "grav_class.h"
#include "grav_inter.h"

int main(void){
    double rA[3] = {0, 0, 0};
    double rB[3] = {1.48e11, 0, 0};
    double pA[3] = {0, 0, 0};
    double pB[3] = {0.3e4, 0, 0};
    // rvector<double> y(buf, 3);
    // rvector<double> z({1, 0, 0});

    // std::cout << y <<std::endl;
    Object objA(2e30, rA, pA);
    Object objB(6e24, rB, pB);
    Object objC(6e24, rB, pB);

    Object objList[2] = {objB, objC};

    // std::cout << vec_diff(objA.r, objB.r) <<std::endl; 
    std::cout << f_2Newton(objA, objB) <<std::endl; 
    std::cout << f_nNewton(objA, objList, 2) <<std::endl; 

    std::cout << pot_2Newton(objA, objB) <<std::endl; 
    std::cout << pot_nNewton(objA, objList, 2) <<std::endl;  
    return 0;
}