#include "grav_Part3_ex.h"

int main (void) {
  double P = 3.06427e7;
  double w = (2*3.14159265)/P;
  struct Parameters params = {2e30, 6e24, 6e3, 1.48e11, w};
 
  std::ofstream fout("Lagrange_Points.txt");

  double x_lo = 2e11, x_hi = 1e17;
  double r2 = find_root(x_lo, x_hi, params);
  std::cout << r2 << std::endl;
  fout << "L2: " << r2 << "\n"; 

  x_lo = -1e20, x_hi = -1e3;
  double r3 = find_root(x_lo, x_hi, params);
  std::cout << r3 << std::endl;
  fout << "L3: " << r3 << "\n"; 

  x_lo = 1e1, x_hi = 1.479e11;
  double r1 = find_root(x_lo, x_hi, params);
  std::cout << r1 << std::endl;
  fout << "L1: " << r1 << "\n";
  fout.close();
}