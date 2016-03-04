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
//    _A[0][0] = 1.0;
//    _A[0][1] = 0.001;
//    _A[1][0] = 0.0116;
//    _A[1][1] = 1.0;
    _A[0][0] = 1.0006;
    _A[0][1] = 0.01;
    _A[1][0] = 0.1161;
    _A[1][1] = 1.0006;
    _B[0][0] = 0.000005;
    _B[1][0] = 0.01;
    _C[0] = -0.00000036654;
    _C[1] = 0.0;
    _D = 0.00016332;
//    _K[0] = 23.1777;
//    _K[1] = 6.8027;
    _K[0] = 22.8283;
    _K[1] = 6.7001;
    _Ki = 5000;

    _T = 0.01;

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
    y = 0.0; //??????
    _xref = 0.0;

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


    /** STATE FEEDBACK WITH INTEGRAL ACTION **/
    _r = _xref - x_real; //model reference
    _x1[0] = _x1[1];
    _x2[0] = _x2[1];
    _z[0] = _z[1];

    _u = -_K[0]*_x1[0] -_K[1]*_x2[0] + _Ki*_z[0];
    y = _C[0]*_x1[0] + _C[1]*_x2[0] + _D*_u;
    //y = _C[0]*_x1[0] + _C[1]*_x2[0];
    _x1[1] = _A[0][0]*_x1[0] + _A[0][1]*_x2[0] + _B[0][0]*_u;
    _x2[1] = _A[1][0]*_x1[0] + _A[1][1]*_x2[0] + _B[1][0]*_u;
    _z[1] = -_C[0]*_x1[0] - _C[1]*_x2[0] + _D*_u + _r;

    cout << "y = " << y << endl;
    cout << "x1 = " << _x1[0] << endl;
    return 0;
}



