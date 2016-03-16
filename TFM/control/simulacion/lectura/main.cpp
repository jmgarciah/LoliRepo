#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <cmath>

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

#include "jr3pci-ioctl.h"
#include "LIPM2d.h"

#define PI  3.141592

using namespace std;

static FILE *fp;

yarp::os::Port port0;
yarp::os::Port port1;

void controlC (void){
    fclose(fp);
    port0.close();
    port1.close();
    exit(-1);
}

int main(void) {
    yarp::os::Network yarp;

    float fz0, mx0, my0; // F-T from sensor 0 in dN*m (0.1N*m)
    float fz1, mx1, my1; // F-T from sensor 1 in dN*m (0.1N*m)

    float xzmp0, yzmp0; // ZMP sensor 0
    float xzmp1, yzmp1; // ZMP sensor 1
    float xzmp = 0.0;
    float yzmp = 0.0;

    LIPM2d eval_x;
    LIPM2d eval_y;

    float angle_x = 0.0;
    float angle_y = 0.0;

    fp = fopen("../data.csv","w+");

    signal (SIGINT, (__sighandler_t) controlC );

    /** Check yarp network**/
    printf("Checking network...\n");
    if (!yarp::os::Network::checkNetwork()) {
        printf("Please start a yarp name server first\n");
        return(-1);
    }
    printf("Network ok\n");

    /** Opening YARP ports**/
    port0.open("/jr3ch0:i");
    port1.open("/jr3ch1:i");
    yarp::os::Network::connect("/jr3ch0:o","/jr3ch0:i");
    yarp::os::Network::connect("/jr3ch1:o","/jr3ch1:i");
 printf("Jr3Yarp connection stablished\n");
    /** SET CONFIG **/
    yarp::os::Property optionsLeftLeg;
    optionsLeftLeg.put("device","remote_controlboard");
    optionsLeftLeg.put("remote","/teo/leftLeg");
    optionsLeftLeg.put("local","/loli/leftLeg");
    yarp::dev::PolyDriver leftLeg(optionsLeftLeg);
    if(!leftLeg.isValid()) {
        printf("TEO device not available.\n");
        leftLeg.close();
        yarp::os::Network::fini();
        return 1;
    }
    yarp::dev::IPositionControl *posLeftLeg;
    bool okLL = leftLeg.view(posLeftLeg);
    if (!okLL) {
        printf("[warning] Problems acquiring robot interface\n");
        return false;
    } else printf("[success] testTEO acquired robot LeftArm interface\n");

    yarp::os::Property optionsRightLeg;
    optionsRightLeg.put("device","remote_controlboard");
    optionsRightLeg.put("remote","/teo/rightLeg");
    optionsRightLeg.put("local","/loli/rightLeg");

    yarp::dev::PolyDriver rightLeg(optionsRightLeg);
    if(!rightLeg.isValid()) {
        printf("TEO device not available.\n");
        rightLeg.close();
        yarp::os::Network::fini();
        return 1;
    }

    yarp::dev::IPositionControl *posRightLeg;
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

    yarp::os::Time::delay(5);
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
        yarp::os::Bottle b0;
        yarp::os::Bottle b1;

        port0.read(b0);
        port1.read(b1);

        fz0 = b0.get(2).asDouble();
        mx0 = b0.get(3).asDouble();
        my0 = b0.get(4).asDouble();

        fz1 = b1.get(2).asDouble();
        mx1 = b1.get(3).asDouble();
        my1 = b1.get(4).asDouble();
	printf("data received\n");
            /** ZMP Equations : Double Support **/
            xzmp0 = -my0 / fz0;
            yzmp0 = mx0 / fz0;

            xzmp1 = -my1 /fz1;
            yzmp1 = mx1 /fz1;

            xzmp = (xzmp0 * fz0 + xzmp1 * fz1) / (fz0 + fz1);
            yzmp = (yzmp0 * fz0 + yzmp1 * fz1) / (fz0 + fz1);

            printf("ZMP = [ %f ,%f]\n", xzmp, yzmp);

            //if ((fz0 == 0.0 ) || ( fz1 == 0.0)) {
            if ((xzmp != xzmp) || (yzmp != yzmp)){
                printf ("Warning: No zmp data\n");
            } else {

                printf ("%d\n", n);

                /** EVALUACION MODELO **/
              //  eval_x.model(xzmp);
                eval_y.model(yzmp);

            //    angle_x = 90-(acos(eval_x.y/1.03)*180/PI);
                angle_y = 90-(acos(eval_y.y/1.03)*180/PI);
             //   printf("angle_x = %f\n", angle_x);
                printf("angle_y = %f\n", angle_y);
             //   posRightLeg->positionMove(4, -angle_x);
             //   posLeftLeg->positionMove(4, -angle_x);

                posRightLeg->positionMove(5, -angle_y); // axial ankle Right Leg
                posRightLeg->positionMove(1, -angle_y); // axial hip Right Leg
                posLeftLeg->positionMove(5, angle_y); // axial ankle Left Leg
                posLeftLeg->positionMove(1, angle_y); // axial hip Left Leg

                fprintf(fp,"\n%d", n);
//                fprintf(fp,",%.15f", eval_x._r);
//                fprintf(fp,",%.15f", xzmp);
//                fprintf(fp,",%.15f", eval_x.y);
//                fprintf(fp,",%f", angle_x);
                fprintf(fp,",%.15f", eval_y._r);
                fprintf(fp,",%.15f", yzmp);
                fprintf(fp,",%.15f", eval_y.y);
                fprintf(fp,",%f", angle_y);
            }

            n++;

        //Sample time = 1ms
        usleep(100000); // delay in microseconds
        //sleep(1);
    }

//    port0.close();
//    port1.close();
}

