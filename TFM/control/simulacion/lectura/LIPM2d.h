/*
 * LIPM2d.h
 *
 *  Created on: 04/12/2015
 *      Author: teo
 */

#ifndef LIPM2D_H_
#define LIPM2D_H_

#include <iostream>
#include <cmath>
#include <yarp/os/all.h>

using namespace std;

class LIPM2d{
public:
    LIPM2d();
    ~LIPM2d();

    float model(float x_real);


    float _r; // reference model signal
    float y; // zmp output signal (to ankle joints)
    float _x1[2]; // state variable

private:
    float _A[2][2];
    float _B[2][1];
    float _C[2];
    float _D;
    float _K[2]; // feedback LQR gain
    float _Ki; // integral gain
    float _T; //sample time
    float _xref; // X_ZMP reference
    float _x2[2]; // state variable
    float _z[3]; // state variable
    float _u; // model control signal

    float _Kp, _Kd;
    float _integral, _derivative;
    float _error, _prev_error;
    float _pid;


};

#endif /* LIPM2D_H_ */
