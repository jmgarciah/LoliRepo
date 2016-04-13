/*
 * 2dLIPM.cpp
 *
 *  Created on: 03/12/2015
 *      Author: teo
 */
#define g		9.81 // Gravity in m/s²
#include <cmath>
#include "LIPM2d.h"




LIPM2d::LIPM2d()
{
    _A[0][0] = 1.003;
    _A[0][1] = 0.03003;
    _A[1][0] = 0.1946;
    _A[1][1] = 1.003;
    _B[0][0] = 0.0004502;
    _B[1][0] = 0.03003;
    _C[0] = -0.974;
    _C[1] = 0.0;
    _D = 0.3266;
    _K[0] = 12.5527;
    _K[1] = 4.9178;
//    _K[0] = 23.18;
//    _K[1] = 6.8;
    _Ki = 100.0;
    _Kd = 0.1;
    _Kp = -3000.0;
    _T = 0.03;

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
    _x1[1] = 5.0*3.1415/180;
    _x2[0] = 0.0;
    _x2[1] = 0.0;
    _z[0] = 0.0;
    _z[1] = 0.0;
    _z[2] = 0.0;
    Ud = 0;
    y = 0.0;
    _pref = 0.0; // ZMP reference
    cout<<"Constructor OK"<<endl;
}

LIPM2d::~LIPM2d(){
}

float LIPM2d::model(float p_real, float reference){
    _pref = reference;
     /** STATE FEEDBACK WITH PID ACTIONS **/
    _r = _pref - p_real; //Variation of ZMP (ZMPref - ZMPreal). Model reference
    _x1[0] = _x1[1];
    _x2[0] = _x2[1];
    _z[0] = _z[1];

    _u = -_K[0]*_x1[0] -_K[1]*_x2[0] + _Kp*(_r-y) + 100*_Ki*_z[0] + _Kd*_z[2];
    y = _C[0]*_x1[0] + _C[1]*_x2[0] + _D*_u;
    _x1[1] = _A[0][0]*_x1[0] + _A[0][1]*_x2[0] + _B[0][0]*_u;
    _x2[1] = _A[1][0]*_x1[0] + _A[1][1]*_x2[0] + _B[1][0]*_u;
    _z[1] = _r - y;
    _z[2] = (_z[1] - _z[0])/_T;

    return 0;
}

float LIPM2d::model2(float reference){
    // IT WORKS BUT MODEL NOT COMPLETE //
    Uref = reference;

    _x1[0] = _x1[1];
    _x2[0] = _x2[1];

    _u = -_K[0]*_x1[0] -_K[1]*_x2[0] - 5500 * Uref;
    y = _C[0]*_x1[0] + _C[1]*_x2[0] + _D*_u;
    _x1[1] = _A[0][0]*_x1[0] + _A[0][1]*_x2[0] + _B[0][0]*_u;
    _x2[1] = _A[1][0]*_x1[0] + _A[1][1]*_x2[0] + _B[1][0]*_u;

    cout << "Uref = " << Uref << endl;
    cout << "x1[0] = " << _x1[0] << endl;
    cout << "x2[0] = " << _x2[0] << endl;
    return 0;
}

float LIPM2d::model3(float reference){
    // DO Nuntitled.figOT WORK // ALWAYS ERROR IN STEADY STATE
     /** STATE FEEDBACK WITH PI ACTIONS **/
    _r = reference;

    _x1[0] = _x1[1];
    _x2[0] = _x2[1];
    _z[0] = _z[1];

    _u = -_K[0]*_x1[0] -_K[1]*_x2[0] + 100*(pre_z + _z[0])*_T - 3000*_z[0];
    y = _C[0]*_x1[0] + _C[1]*_x2[0] + _D*_u;
    _x1[1] = _A[0][0]*_x1[0] + _A[0][1]*_x2[0] + _B[0][0]*_u;
    _x2[1] = _A[1][0]*_x1[0] + _A[1][1]*_x2[0] + _B[1][0]*_u;
    _z[1] = _r - y;
    pre_z = _z[0];

    return 0;
}


float LIPM2d::model4(float reference){
    // COMPLETE MODEL WITH UD //
     /** STATE FEEDBACK WITH INTEGRAL ACTION **/
    _r = reference;

    _x1[0] = _x1[1];
    _x2[0] = _x2[1];
    _z[0] = _z[1];
    Ud = sin(_r/1.03);

    _u = -_K[0]*_x1[0] -_K[1]*_x2[0] + 10.0*(pre_z + _z[0])*_T - 1.5*_z[0] - 2.05*Ud;
    y = _C[0]*_x1[0] + _C[1]*_x2[0] + _D*_u;
    _x1[1] = _A[0][0]*_x1[0] + _A[0][1]*_x2[0] + _B[0][0]*_u;
    _x2[1] = _A[1][0]*_x1[0] + _A[1][1]*_x2[0] + _B[1][0]*_u;
    _z[1] = _r - y;


    pre_z = _z[0];

    return 0;
}
