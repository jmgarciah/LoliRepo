#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

#include <sys/ioctl.h>

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

#include "jr3pci-ioctl.h"
#include "LIPM2d.h"

using namespace std;
using namespace yarp::os;
using namespace yarp::dev;

int main(void) {

    yarp::os::Network yarp;
    yarp::os::Port port;

    six_axis_array fm0, fm1;
    force_array fs0, fs1;
    int ret, fd;
    LIPM2d modelo;

    int f00,f01,f02,m00,m01,m02; // F-T from the sensor 0 in Newton
    int f10,f11,f12,m10,m11,m12; // F-T from the sensor 1 in Newton
    float fx0, fy0, fz0, mx0, my0, mz0; // Scaled F-T from sensor 0 in dN*m (0.1N*m)
    float fx1, fy1, fz1, mx1, my1, mz1; // Scaled F-T from sensor 1 in dN*m (0.1N*m)
    float xzmp0, yzmp0; // ZMP sensor 0
    float xzmp1, yzmp1; // ZMP sensor 1
    float xzmp = 0.0;
    float yzmp = 0.0;
    FILE *fp;

    fp = fopen("../data.csv","w+");


    /** Check yarp network**/
    printf("Checking network...\n");
    if (!Network::checkNetwork()) {
        printf("Please start a yarp name server first\n");
        return(-1);
    }
    printf("Network ok\n");
    //Puerto local
    port.open("/jr3:o");

    printf("Opening device ...\n");
    if ((fd=open("/dev/jr3",O_RDWR)) < 0) {
        perror("Can't open device. No way to read force!");
        // exit(1);
    }

    printf("Getting full scales...\n");
    ret=ioctl(fd,IOCTL0_JR3_GET_FULL_SCALES,&fs0);
    printf("Full scales of Sensor 0 are %d %d %d %d %d %d\n",fs0.f[0],fs0.f[1],fs0.f[2],fs0.m[0],fs0.m[1],fs0.m[2]);
    ret=ioctl(fd,IOCTL1_JR3_GET_FULL_SCALES,&fs1);
    printf("Full scales of Sensor 1 are: %d %d %d %d %d %d\n", fs1.f[0],fs1.f[1],fs1.f[2],fs1.m[0],fs1.m[1],fs1.m[2]);
    ret=ioctl(fd,IOCTL0_JR3_ZEROOFFS);
    ret=ioctl(fd,IOCTL1_JR3_ZEROOFFS);

    /** SET CONFIG **/
    Property optionsLeftLeg;
    optionsLeftLeg.put("device","remote_controlboard");
    optionsLeftLeg.put("remote","/teo/leftLeg");
    optionsLeftLeg.put("local","/loli/leftLeg");
    PolyDriver leftLeg(optionsLeftLeg);
    if(!leftLeg.isValid()) {
        printf("TEO device not available.\n");
        leftLeg.close();
        Network::fini();
        return 1;
    }
    IPositionControl *posLeftLeg;
    bool okLL = leftLeg.view(posLeftLeg);
    if (!okLL) {
        printf("[warning] Problems acquiring robot interface\n");
        return false;
    } else printf("[success] testTEO acquired robot LeftArm interface\n");

    Property optionsRightLeg;
    optionsRightLeg.put("device","remote_controlboard");
    optionsRightLeg.put("remote","/teo/rightLeg");
    optionsRightLeg.put("local","/loli/rightLeg");

    PolyDriver rightLeg(optionsRightLeg);
    if(!rightLeg.isValid()) {
        printf("TEO device not available.\n");
        rightLeg.close();
        Network::fini();
        return 1;
    }

    IPositionControl *posRightLeg;
    bool okRL = rightLeg.view(posRightLeg);
    if (!okRL) {
        printf("[warning] Problems acquiring robot interface\n");
        return false;
    } else printf("[success] testTEO acquired robot RightArm inteface\n");


    /** SET MODE **/
    printf("Set position mode Left Leg");
    posLeftLeg->setPositionMode();
    printf("Set position mode Left Leg");
    posRightLeg->setPositionMode();

    Time::delay(5);
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

    int ok;
    cin >> ok; // confirmacion de empiece

    int n = 1;
    while (ok) {
        yarp::os::Bottle bottle;

        ret=ioctl(fd,IOCTL0_JR3_FILTER0,&fm0);
        ret=ioctl(fd,IOCTL1_JR3_FILTER0,&fm1);

        if (ret!=-1) {

            // -------- SENSOR 0 ------------ //

            f00 = 100*fm0.f[0]*fs0.f[0]/16384;
            f01 = 100*fm0.f[1]*fs0.f[1]/16384;
            f02 = 100*fm0.f[2]*fs0.f[2]/16384;
            m00 = 10*fm0.m[0]*fs0.m[0]/16384;
            m01 = 10*fm0.m[1]*fs0.m[1]/16384;
            m02 = 10*fm0.m[2]*fs0.m[2]/16384;
            fx0 = (float) f00/100;
            fy0 = (float) f01/100;
            fz0 = (float) f02/100;
            mx0 = (float) m00/100;
            my0 = (float) m01/100;
            mz0 = (float) m02/100;

            // -------- SENSOR 1 ------------ //
            f10 = 100*fm1.f[0]*fs1.f[0]/16384;
            f11 = 100*fm1.f[1]*fs1.f[1]/16384;
            f12 = 100*fm1.f[2]*fs1.f[2]/16384;
            m10 = 10*fm1.m[0]*fs1.m[0]/16384;
            m11 = 10*fm1.m[1]*fs1.m[1]/16384;
            m12 = 10*fm1.m[2]*fs1.m[2]/16384;
            fx1 = (float) f10/100;
            fy1 = (float) f11/100;
            fz1 = (float) f12/100;
            mx1 = (float) m10/100;
            my1 = (float) m11/100;
            mz1 = (float) m12/100;

            /** ZMP Equations : Double Support **/
            xzmp0 = -my0 / fz0;
            yzmp0 = mx0 / fz0;

            xzmp1 = -my1 /fz1;
            yzmp1 = mx1 /fz1;

            xzmp = (xzmp0 * fz0 + xzmp1 * fz1) / (fz0 + fz1);
            yzmp = (yzmp0 * fz0 + yzmp1 * fz1) / (fz0 + fz1);

            printf("%f , %f\n", fz0, fz1);
            printf("ZMP = [ %f ,%f]\n", xzmp, yzmp);

            //if ((fz0 == 0.0 ) || ( fz1 == 0.0)) {
            if ((xzmp != xzmp) || (yzmp != yzmp)){
                printf ("Warning: No zmp data\n");
            } else {

                /** EVALUACION MODELO **/
                modelo.model(xzmp, yzmp);

                posRightLeg->positionMove(4, modelo._u);
                posLeftLeg->positionMove(4, modelo._u);

                cout << "model ok" << endl;

                //modelo.sendData(port1, data);

                //            bottle.addDouble(modelo._x1);
                //            bottle.addDouble(modelo._x2);
                //            bottle.addDouble(modelo._u);
                //            bottle.addDouble(modelo._y);
                //            bottle.addDouble(xzmp);
                //            bottle.addDouble(yzmp);

                port.write(bottle);

                fprintf(fp,"\n%d", n);
                fprintf(fp,",%f", xzmp);
                fprintf(fp,",%f", yzmp);
                fprintf(fp,",%f", modelo._x_model[0]);
                fprintf(fp,",%f", modelo._y_model[0]);
                fprintf(fp,",%f", modelo._u);
                fprintf(fp,",%f", modelo._par);
            }

            n++;



        } else perror("");

        //Sample time = 1ms
        usleep(100000); // delay in microseconds
        //sleep(1);
    }

    fclose(fp);
    close(fd);
}

