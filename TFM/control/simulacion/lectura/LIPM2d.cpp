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
//    _K[0] = 18.8952;
//    _K[1] = 6.1427;
    _K[0] = 23.18;
    _K[1] = 6.8;
//    _K[0] = 42.3;
//    _K[1] = 9.19;
    _Ki = 10.0;
    _Kd = 10.0;
    _Kp = -5000.0;
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
    y = 0.0; //??????
    _xref = 0.0;

    _integral = 0.0;
    _derivative = 0.0;
    _error = 0.0;
    _prev_error = 0.0;
    _pid = 0.0;

}

LIPM2d::~LIPM2d(){
}

float LIPM2d::model(float x_real){

    /** Evaluacion modelo con offset zmp **/
    /**
    _x_model[0] = _x_model[1];
    _y_model[0] = _y_model[1];
    _x_error = x_real - _x_model[0];
    _y_error = y_real - _y_model[0];
    _u = _r-(_K[0]*_x_error + _K[1]*_y_error);
    _par = _C[0]*_x_error + _C[1]*_y_error + _D*_u;

    _x_model[1] = _A[0][0]*_x_model[0] + _A[0][1]*_y_model[0] + _B[0][0]*_u;
    _y_model[1] = _A[1][0]*_x_model[0] + _A[1][1]*_y_model[0] + _B[1][0]*_u;

    cout << "x_model[0] = " << _x_model[0] << endl;
    cout << "x_model[0] = " << _y_model[0] << endl;
    cout << "y_model[1] = " << _x_model[1] << endl;
    cout << "y_model[1] = " << _y_model[1] << endl;
    cout << "u = " << _u << endl;
    cout << "par = " << _par << endl;
    **/


//    /** STATE FEEDBACK WITH INTEGRAL ACTION **/
//    _r = _xref - x_real; //model reference
//    _x1[0] = _x1[1];
//    _x2[0] = _x2[1];
//    _z[0] = _z[1];

//    _error = _r - y;
//    _integral = _integral + _error*0.005;
//    _derivative = (_error - _prev_error)/0.005;
//    _pid = _Kp *_error + _Ki*_integral + _Kd*_derivative;

//   // _u = -_K[0]*_x1[0] -_K[1]*_x2[0] + _Ki*_z[0];
//    _u = -_K[0]*_x1[0] -_K[1]*_x2[0] + _pid;
//    y = _C[0]*_x1[0] + _C[1]*_x2[0] + _D*_u;
//    //y = _C[0]*_x1[0] + _C[1]*_x2[0];
//    _x1[1] = _A[0][0]*_x1[0] + _A[0][1]*_x2[0] + _B[0][0]*_u;
//    _x2[1] = _A[1][0]*_x1[0] + _A[1][1]*_x2[0] + _B[1][0]*_u;
//    //_z[1] = _r -_C[0]*_x1[0] - _C[1]*_x2[0] - _D*_u;
//    //_z[1] = _r - y;

//    _prev_error = _error;

//    cout << "r = " << _r << endl;
//    cout << "y = " << y << endl;
//    cout << "x1 = " << _x1[0] << endl;

     /** STATE FEEDBACK WITH PRECOMPENSATOR GAIN **/
    _r = _xref - x_real; //model reference

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
    cout << "x1 = " << _x1[0] << endl;
    return 0;
}



