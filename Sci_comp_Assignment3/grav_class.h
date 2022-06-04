#ifndef GRAV_CLASS_H
#define GRAV_CLASS_H
#include <iostream>
#include <rarray>

class Object{
    public:
        double  M;                       // Mass of Object
        rvector<double>  r0;             // Initial Position
        rvector<double>  p0;             // Initial Momentum
        rvector<double>  r;              // Current Position
        rvector<double>  p;              // Current Momentum
        rvector<double>  f;              // Current Force

        Object(double x, double y[], double z[]){ // Constructor
            M = x;
            rvector<double> buf1(y, 3);
            r0 = buf1.copy();
            r = buf1.copy();
         
            rvector<double> buf2(z,3);
            p0 = buf2.copy();
            p = buf2.copy();
        }
        void update(double y[], double z[]){ // setter
            rvector<double> buf1(y, 3);
            r = buf1.copy();
        
            rvector<double> buf2(z,3);
            p = buf2.copy();
        }
};

#endif