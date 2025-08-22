#include <iostream>
#include "matrix.h"
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif



vector<vector<double>> intialize_T(double theta, double alpha, double r, double d){  
  
  theta = theta * M_PI / 180.0;
  alpha = alpha * M_PI / 180.0;
  
  vector<vector<double>> T = {
    {
      cos(theta), -sin(theta) * cos(alpha), sin(theta) * sin(alpha), r * cos(theta)
    },
    {
      sin(theta), cos(theta) * cos(alpha), - cos(alpha) * sin(alpha), r * sin(theta)
    },
    {
      0, sin(alpha), cos(alpha), d
    },
    {
      0, 0, 0, 1
    }
  };

  return T;
}

int main(){
    vector<vector<double>> T1 = intialize_T(30, 45, 2, 1);
    vector<vector<double>> T2 = intialize_T(45, 50, 1, 2);

    double a_m[4][4];
    double b_m[4][4];

    for(int i=0; i<T1.size(); i++){
      for(int j=0; j<T1[0].size(); j++){
        a_m[i][j] = T1[i][j];
        b_m[i][j] = T2[i][j];
      }
    }

    Matrix<double> a(ARRAY_SIZE(a_m), ARRAY_SIZE(a_m[0]), a_m[0], ARRAY_SIZE(a_m)*ARRAY_SIZE(a_m[0]));
    Matrix<double> b(ARRAY_SIZE(b_m), ARRAY_SIZE(b_m[0]), b_m[0], ARRAY_SIZE(b_m)*ARRAY_SIZE(b_m[0]));
    Matrix<double> c;

  try {
        c = a * b;
        for (unsigned int i = 0; i < c.rowNum(); i++) {
            for (unsigned int j = 0; j < c.colNum(); j++) {
                std::cout << setw(12) << fixed << setprecision(6) << c[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    } catch (MatrixException& e) {
        std::cerr << e.message() << std::endl;
        return e.errorCode();
    }
}
