#ifndef _ratethread_H_
#define _ratethread_H_

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include "LIPM2d.h"

static FILE *fp;

yarp::os::Port port0;
yarp::os::Port port1;
yarp::dev::IPositionControl *posRightLeg;
yarp::dev::IPositionControl *posLeftLeg;

class MyRateThread : public yarp::os::RateThread
{
public:
    MyRateThread() : yarp::os::RateThread(T*1000.0) {
        n = 1;
    }
    void run(){
        getInitialTime();
        readFTSensor();
        zmpComp();
        evaluateModel();
        setJoints();
        printData();
        saveToFile();
        n++;
    }
    void getInitialTime()
    {
        if (n==1)
        {
            init_time = yarp::os::Time::now();
        }
        //init_loop = yarp::os::Time::now();
    }
    void getCurrentTime(){
        curr_time = yarp::os::Time::now() - init_time;
    }

    void readFTSensor(){
        yarp::os::Bottle b0;
        yarp::os::Bottle b1;
        port0.read(b0);
        port1.read(b1);

        _fz0 = b0.get(0).asDouble();
        _mx0 = b0.get(3).asDouble();
        _my0 = b0.get(4).asDouble();

        _fz1 = b1.get(0).asDouble();
        _mx1 = b1.get(3).asDouble();
        _my1 = b1.get(4).asDouble();
    }

    void zmpComp(){
        /** ZMP Equations : Double Support **/
        _xzmp0 = -_my0 / _fz0;
        _yzmp0 = _mx0 / _fz0;

        _xzmp1 = -_my1 /_fz1;
        _yzmp1 = _mx1 /_fz1;

        _xzmp = (_xzmp0 * _fz0 + _xzmp1 * _fz1) / (_fz0 + _fz1);
        _yzmp = (_yzmp0 * _fz0 + _yzmp1 * _fz1) / (_fz0 + _fz1);
    }

    void homing(){
        /** SET LEFT LEG TO 0 **/
        printf("Left Leg positionMove(0,0)\n");
        posLeftLeg->positionMove(0, 0);
        printf("Left Leg positionMove(1,0)\n");
        posLeftLeg->positionMove(1, 0);
        printf("Left Leg positionMove(2,0)\n");
        posLeftLeg->positionMove(2, 0);
        printf("Left Leg positionMove(3,0)\n");
        posLeftLeg->positionMove(3, 0);
        printf("Left Leg positionMove(4,0)\n");
        posLeftLeg->positionMove(4, 0);
        printf("Left Leg positionMove(5,0)\n");
        posLeftLeg->positionMove(5, 0);

        /** SET RIGHT LEG TO ZERO **/
        printf("Right Leg positionMove(0,0)\n");
        posRightLeg->positionMove(0, 0);
        printf("Right Leg positionMove(1,0)\n");
        posRightLeg->positionMove(1, 0);
        printf("Right Leg positionMove(2,0)\n");
        posRightLeg->positionMove(2, 0);
        printf("Right Leg positionMove(3,0)\n");
        posRightLeg->positionMove(3, 0);
        printf("Right Leg positionMove(4,0)\n");
        posRightLeg->positionMove(4, 0);
        printf("Right Leg positionMove(5,0)\n");
        posRightLeg->positionMove(5, 0);
    }
    void evaluateModel(){
        /** EVALUACION MODELO **/
        //  eval_x.model(xzmp);
        _eval_y.model(_yzmp);

        //    angle_x = 90-(acos(eval_x.y/1.03)*180/PI);
        angle_y = 90-(acos(_eval_y.y/1.03)*180/PI);
        //   printf("angle_x = %f\n", angle_x);
        //   printf("angle_y = %f\n", angle_y);
        //   posRightLeg->positionMove(4, -angle_x);
        //   posLeftLeg->positionMove(4, -angle_x);
    }
    void setJoints(){
        posRightLeg->positionMove(5, -angle_y); // axial ankle Right Leg
        posRightLeg->positionMove(1, -angle_y); // axial hip Right Leg
        posLeftLeg->positionMove(5, angle_y); // axial ankle Left Leg
        posLeftLeg->positionMove(1, angle_y); // axial hip Left Leg
    }
    void printData(){
        cout << "ZMP = [" << _xzmp << ", " << _yzmp << "]" << endl;
        cout << "Ref = " << _eval_y._r << endl;
        cout << "y_model = " << _eval_y.y << endl;
        cout << "angle_y = " << angle_y << endl;
    }
    void saveToFile()
    {
        fprintf(fp,"\n%d", n);
        //                fprintf(fp,",%.15f", eval_x._r);
        //                fprintf(fp,",%.15f", xzmp);
        //                fprintf(fp,",%.15f", eval_x.y);
        //                fprintf(fp,",%f", angle_x);
        fprintf(fp,",%.15f", _eval_y._r);
        fprintf(fp,",%.15f", _yzmp);
        fprintf(fp,",%.15f", _eval_y.y);
        fprintf(fp,",%f", angle_y);
    }


private:
    int n;
    LIPM2d _eval_x;
    LIPM2d _eval_y;
    float _fz0, _mx0, _my0; // F-T from sensor 0 in dN*m (0.1N*m)
    float _fz1, _mx1, _my1; // F-T from sensor 1 in dN*m (0.1N*m)

    float _xzmp0, _yzmp0; // ZMP sensor 0
    float _xzmp1, _yzmp1; // ZMP sensor 1
    float _xzmp; // Global x_ZMP
    float _yzmp; // Global y_ZMP

    float angle_x;
    float angle_y;

    double init_time, init_loop, curr_time;
};

#endif //_ratethread_H_
