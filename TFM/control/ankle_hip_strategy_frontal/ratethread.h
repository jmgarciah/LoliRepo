#ifndef _ratethread_H_
#define _ratethread_H_

#include "LIPM2d.h"

static FILE *fp;

yarp::os::Port port0;
yarp::os::Port port1;
yarp::dev::IPositionControl *posRightLeg;
yarp::dev::IPositionControl *posLeftLeg;


class MyRateThread : public yarp::os::RateThread
{
public:
    MyRateThread() : yarp::os::RateThread(TS*1000.0){
        n = 1;
        e = 0.194;
    }
    void run(){
        printf("----------\n Running\n");
        _dt = n*TS;
        ref = 0.0;
        getInitialTime();
        readFTSensor();
        zmpComp();
        evaluateModel();
        setJoints();
        printData();
        saveToFile();
        n++;
        getCurrentTime();
        double t = curr_time - init_loop;
        printf("LoopTime = %f\n",t);
    }
    void getInitialTime()
    {
        init_loop = yarp::os::Time::now();
    }
    void getCurrentTime(){
        curr_time = yarp::os::Time::now();
    }

    void readFTSensor(){
        yarp::os::Bottle b0;
        yarp::os::Bottle b1;
        port0.read(b0);
        port1.read(b1);

        _fx0 = b0.get(0).asDouble();
        _fy0 = b0.get(1).asDouble();
        _fz0 = b0.get(2).asDouble();
        _mx0 = b0.get(3).asDouble();
        _my0 = b0.get(4).asDouble();

        _fx1 = b1.get(0).asDouble();
        _fy1 = b1.get(1).asDouble();
        _fz1 = b1.get(2).asDouble();
        _mx1 = b1.get(3).asDouble();
        _my1 = b1.get(4).asDouble();
    }

    void zmpComp(){
        /** ZMP Equations : Double Support **/
        _xzmp0 = -(_my0 + e*_fx0) / _fz0;
        _yzmp0 = (_mx0 + e*_fy0) / _fz0;

        _xzmp1 = -(_my1 + e*_fx1) /_fz1;
        _yzmp1 = (_mx1 + e*_fy1) /_fz1;

        _xzmp = (_xzmp0 * _fz0 + _xzmp1 * _fz1) / (_fz0 + _fz1);
        _yzmp = (_yzmp0 * _fz0 + _yzmp1 * _fz1) / (_fz0 + _fz1);
        
        // OFFSET
        if (n >=0 && n < 10){
            sum = _xzmp + sum;
            offs_x = sum / n;
        }
        _xzmp = (_xzmp - offs_x);
        _yzmp = _yzmp - offs_y;
        
        if ((_xzmp != _xzmp) || (_yzmp != _yzmp)){
            printf ("Warning: No zmp data\n");
        }
    }

    void evaluateModel(){
        /** EVALUACION MODELO **/
        //_eval_x.model(_xzmp, ref);
        _eval_y.model(_yzmp, ref);

        //angle_x = -1.6*asin(_eval_x.y/1.03)*180/PI;
        angle_y = asin(_eval_y.y/1.03)*180/PI;

    }
    void setJoints(){
        // posRightLeg->positionMove(4, angle_x);
        // posLeftLeg->positionMove(4, angle_x);
        posRightLeg->positionMove(5, -angle_y); // axial ankle Right Leg
        posRightLeg->positionMove(1, angle_y); // axial hip Right Leg
        posLeftLeg->positionMove(5, -angle_y); // axial ankle Left Leg
        posLeftLeg->positionMove(1, angle_y); // axial hip Left Leg
    }
    void printData(){
        cout << "t = " << _dt << endl;
        cout << "ZMP = [" << _xzmp << ", " << _yzmp << "]" << endl;
        cout << "Azmp = " << _eval_y._zmp_error << endl;
        cout << "y_model = " << _eval_y.y << endl;
        cout << "angle_y = " << angle_y << endl;
    }
    void saveToFile()
    {
        fprintf(fp,"\n%d", n);
        fprintf(fp,",%.4f",_dt);
        fprintf(fp,",%.15f", _yzmp);
        fprintf(fp,",%.15f", _eval_y.y);
        fprintf(fp,",%.15f", _eval_y._x1[0]);
        fprintf(fp,",%.15f", _eval_y._zmp_ref);
        fprintf(fp,",%f", _eval_y._u);
        fprintf(fp,",%f", angle_x);
    }


private:
    int n;
    //LIPM2d _eval_x;
    LIPM2d _eval_y;
    float _fx0, _fy0, _fz0, _mx0, _my0; // F-T from sensor 0
    float _fx1, _fy1, _fz1, _mx1, _my1; // F-T from sensor 1

    float e; // distance [m] between ground and sensor center
    float offs_x; // zmp offset in initial time.
    float offs_y;
    float sum;
    float _xzmp0, _yzmp0; // ZMP sensor 0
    float _xzmp1, _yzmp1; // ZMP sensor 1
    float _xzmp; // Global x_ZMP
    float _yzmp; // Global y_ZMP

    float angle_x;
    float angle_y;

    double init_time, init_loop, curr_time, _dt;

    float ref;
};

#endif //_ratethread_H_
