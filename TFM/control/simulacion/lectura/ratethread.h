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
float ref = 0.0;


class MyRateThread : public yarp::os::RateThread
{
public:
    MyRateThread() : yarp::os::RateThread(TS*1000.0){
        n = 1;

    }
    void run(){
        printf("----------\n Running\n");
        _dt = n*TS;
        getInitialTime();
        //readFTSensor();
        //zmpComp();
        //_xzmp = 0.1;
        //ref = 0.1;
        if (_dt > 2.0 && _dt < 6.0){
            ref = log(_dt)-0.7;
        }
        evaluateModel();
        //setJoints();
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

        _fz0 = b0.get(2).asDouble();
        _mx0 = b0.get(3).asDouble();
        _my0 = b0.get(4).asDouble();

        _fz1 = b1.get(2).asDouble();
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
        if ((_xzmp != _xzmp) || (_yzmp != _yzmp)){
            printf ("Warning: No zmp data\n");
        }
    }

    void evaluateModel(){
        /** EVALUACION MODELO **/
        //  _eval_x.model(_xzmp,ref);
          _eval_x.model(ref);
       // _eval_y.model(_yzmp);

         //   angle_x = -90+(acos(_eval_x.y/1.03)*180/PI);
        // angle_y = 90-(acos(_eval_y.y/1.03)*180/PI);
        //   printf("angle_x = %f\n", angle_x);
        //   printf("angle_y = %f\n", angle_y);
    }
    void setJoints(){
        posRightLeg->positionMove(4, angle_x);
        posLeftLeg->positionMove(4, angle_x);
//        posRightLeg->positionMove(5, -angle_y); // axial ankle Right Leg
//        posRightLeg->positionMove(1, -angle_y); // axial hip Right Leg
//        posLeftLeg->positionMove(5, angle_y); // axial ankle Left Leg
//        posLeftLeg->positionMove(1, angle_y); // axial hip Left Leg
    }
    void printData(){
        cout << "t = " << _dt << endl;
        cout << "ZMP = [" << _xzmp << ", " << _yzmp << "]" << endl;
        cout << "Ref = " << ref << endl;
        //cout << "Azmp = " << _eval_x._r << endl;
        cout << "x_model = " << _eval_x.y << endl;
        cout << "x1[0] = " << _eval_x._x1[0] << endl;
        cout << "Ud[0] = " << _eval_x._u_ref << endl;
        //cout << "angle_x = " << angle_x << endl;
    }
    void saveToFile()
    {
          fprintf(fp,"\n%d", n);
          fprintf(fp,",%.4f",_dt);
          //fprintf(fp,",%.15f",_eval_x._r);
          fprintf(fp,",%.15f",ref);
          //fprintf(fp,",%.15f", _xzmp);
          fprintf(fp,",%.15f", _eval_x.y);
          fprintf(fp,",%.15f", _eval_x._x1[0]);
          fprintf(fp,",%.15f", _eval_x._u_ref);
          //fprintf(fp,",%f", angle_x);

//        fprintf(fp,",%.15f", _eval_y._r);
//        fprintf(fp,",%.15f", _yzmp);
//        fprintf(fp,",%.15f", _eval_y.y);
//        fprintf(fp,",%f", angle_y);
    }


private:
    int n;
    LIPM2d _eval_x;
    //LIPM2d _eval_y;
    float _fz0, _mx0, _my0; // F-T from sensor 0 in dN*m (0.1N*m)
    float _fz1, _mx1, _my1; // F-T from sensor 1 in dN*m (0.1N*m)

    float _xzmp0, _yzmp0; // ZMP sensor 0
    float _xzmp1, _yzmp1; // ZMP sensor 1
    float _xzmp; // Global x_ZMP
    float _yzmp; // Global y_ZMP

    float angle_x;
    float angle_y;

    double init_time, init_loop, curr_time, _dt;
};

#endif //_ratethread_H_
