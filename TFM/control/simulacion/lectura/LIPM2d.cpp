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
    A[0][0] = 1.0;
    A[0][1] = 0.001;
    A[1][0] = 0.0116;
    A[1][1] = 1.0;
    B[0][0] = 0.0;
    B[1][0] = 0.001;
    C[0] = 0.000224;
    C[1] = 0.0;
    D = -0.1;
    K[0] = 23.177;
    K[1] = 6.8027;

    _T = 0.001;

    cout << "Discrete-time Space State Model description:" << endl;
    cout << "\n A = " << endl;
    cout << "\t x1 \t x2" << endl;
    cout << "x1 \t " << A[0][0] << "\t " << A[0][1] << endl;
    cout << "x2 \t " << A[1][0] << "\t " << A[1][1] << endl;
    cout << "\n B = " << endl;
    cout << "\t u" << endl;
    cout << "x1 \t " << B[0][0] << endl;
    cout << "x2 \t " << B[1][0] << endl;
    cout << "\n C = " << endl;
    cout << "\t x1 \t x2" << endl;
    cout << "y \t " << C[0] << "\t " << C[1] << endl;
    cout << "\n D = " << endl;
    cout << "\t u" << endl;
    cout << "y \t " << D << endl;
    cout << "\nLinear Quadratic Regulator gain:" << endl;
    cout << "K = [ " << K[0] << " , "<< K[1] << " ]" << endl;
    cout << "\nSample Time : " << _T << " s" << endl;

    // Inicializacion variables
    _r = 0;
    _u = 0.0;
    _y = 0.0;
    _x1[0] = 1.0;
    _x2[0] = 1.0;
    _x1[1] = 1.0;
    _x2[1] = 1.0;

}

LIPM2d::~LIPM2d(){
}

float LIPM2d::model(float px, float py){
    /**
     * Linear inverted pendulum model in discrete state space
     * x[k+1] = Ax[k] + Bu[k]
     * y[k] = Cx[k] + Du[k]
     **/
    /** Evaluacion modelo con zmp calculado **/
    _x1[0] = _x1[1];
    _x2[0] = _x2[1];
    _u = _r-(K[0]*_x1[0]+K[1]*_x2[0]);
    _y = C[0]*_x1[0] + C[1]*_x2[0] + D*_u;
    _x1[1] = A[0][0]*_x1[0] + A[0][1]*_x2[0] + B[0][0]*_u;
    _x2[1] = A[1][0]*_x1[0] + A[1][1]*_x2[0] + B[1][0]*_u;

    cout << "x1[0] = " << _x1[0] << endl;
    cout << "x2[0] = " << _x2[0] << endl;
    cout << "x1[1] = " << _x1[1] << endl;
    cout << "x2[1] = " << _x2[1] << endl;
    cout << "u = " << _u << endl;
    cout << "y = " << _y << endl;

    /** Evaluacion modelo con datos zmp reales **/
//    _x1 = px;
//    _x2 = py;
//    _u = _r-(K[0]*_x1+K[1]*_x2);
//    _y = C[0]*_x1 + C[1]*_x2 + D*_u;

//    cout << "x1 = " << _x1 << endl;
//    cout << "x2 = " << _x2 << endl;
//    cout << "u = " << _u << endl;
//    cout << "y = " << _y << endl;
    return 0;
}


//void LIPM2d::sendData(yarp::os::Port port, yarp::os::Bottle bottle){

