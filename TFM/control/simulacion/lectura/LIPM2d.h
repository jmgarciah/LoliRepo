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

    float model(float px, float py);
   // void sendData(yarp::os::Port port, yarp::os::Bottle bottle);
    float _x_model[2];
    float _y_model[2];
    float _x_error;
    float _y_error;
    float _u; //control signal
    float _par; //torque output

private:
    float A[2][2];
    float B[2][1];
    float C[2];
    float D;
    float K[2];
    float _T; //sample time
    float _r; //reference signal

};




#endif /* LIPM2D_H_ */
