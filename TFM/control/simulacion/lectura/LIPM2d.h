/*
 * LIPM2d.h
 *
 *  Created on: 04/12/2015
 *      Author: teo
 */

#ifndef LIPM2D_H_
#define LIPM2D_H_

#include <iostream>
#include <yarp/os/all.h>


using namespace std;

class LIPM2d{
public:
    LIPM2d();
    ~LIPM2d();

    float model(float p_real, float reference);
    float model2(float reference);
    float model3(float reference);
    float model4(float reference);

    float _x1[2]; // state variable
    float _x2[2]; // model state variable
    float _r; // reference model signal
    float y; // zmp output signal (to ankle joints)
    float Ud; // comanded angle

private:
    float _A[2][2];
    float _B[2][1];
    float _C[2];
    float _D;
    float _K[2]; // feedback LQR gain
    float _Kp, _Ki, _Kd; // P, I, D gains
    float _T; // sample time
    float _pref; // ZMP reference

    float _z[3]; // model state variable
    float _u; // model control signal
    float Uref;
    float pre_z;

};

#endif /* LIPM2D_H_ */
