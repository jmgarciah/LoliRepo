/*
 * 2dLIPM.cpp
 *
 *  Created on: 03/12/2015
 *      Author: teo
 */
#define g		9.81 // Gravity in m/s²
#include "LIPM2d.h"




LIPM2d::LIPM2d()
{
    _A[0][0] = 1.0;
    _A[0][1] = 0.001;
    _A[1][0] = 0.009462;
    _A[1][1] = 1.0;
    _B[0][0] = 0.0000005;
    _B[1][0] = 0.001;
    _C[0] = -0.0000002435;
    _C[1] = 0.0;
    _D = 0.00016332;
    _K[0] = 18.8952;
    _K[1] = 6.1427;
//    _K[0] = 23.18;
//    _K[1] = 6.8;
    _Ki = 10.0;
    _Kd = 10.0;
    _Kp = -3000.0;
    _T = 0.001;

    cout << "Discrete-time Space State Model description:" << endl;
    cout << "\n A = " << endl;
    cout << "\t x1 \t x2" << endl;
    cout << "x1 \t " << _A[0][0] << "\t " << _A[0][1] << endl;
    cout << "x2 \t " << _A[1][0] << "\t " << _A[1][1] << endl;
    cout << "\n B = " << endl;
    cout << "\t u" << endl;
    cout << "x1 \t " << _B[0][0] << endl;
    cout << "x2 \t " << _B[1][0] << endl;
    cout << "\n C = " << endl;
    cout << "\t x1 \t x2" << endl;
    cout << "y \t " << _C[0] << "\t " << _C[1] << endl;
    cout << "\n D = " << endl;
    cout << "\t u" << endl;
    cout << "y \t " << _D << endl;
    cout << "\nLinear Quadratic Regulator gain:" << endl;
    cout << "K = [ " << _K[0] << " , "<< _K[1] << " ]" << endl;
    cout << "\nSample Time : " << _T << " s" << endl;

    // Inicializacion variables
    _r = 0.0;
    _u = 0.0;
    _x1[0] = 0.0;
    _x1[1] = 0.0;
    _x2[0] = 0.0;
    _x2[1] = 0.0;
    _z[0] = 0.0;
    _z[1] = 0.0;
    _z[2] = 0.0;
    y = 0.0;
    _pref = 0.0;

}

LIPM2d::~LIPM2d(){
}

float LIPM2d::model(float p_real){


     /** STATE FEEDBACK WITH PID ACTIONS **/
    _r = _pref - p_real; //model reference

    _x1[0] = _x1[1];
    _x2[0] = _x2[1];
    _z[0] = _z[1];

    _u = -_K[0]*_x1[0] -_K[1]*_x2[0] + _Kp*(_r-y) + _Ki*_z[0] + _Kd*_z[2];
    y = _C[0]*_x1[0] + _C[1]*_x2[0] + _D*_u;
    _x1[1] = _A[0][0]*_x1[0] + _A[0][1]*_x2[0] + _B[0][0]*_u;
    _x2[1] = _A[1][0]*_x1[0] + _A[1][1]*_x2[0] + _B[1][0]*_u;
    _z[1] = _r - y;
    _z[2] = (_z[1] - _z[0])/0.005;

    cout << "r = " << _r << endl;
    cout << "y = " << y << endl;

    return 0;
}



