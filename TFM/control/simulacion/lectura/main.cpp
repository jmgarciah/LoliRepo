#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

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

    six_axis_array fm;
    force_array fs;
    int ret, fd;
    LIPM2d modelo;
    float xzmp = 0.0;
    float yzmp = 0.0;

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
    ret=ioctl(fd,IOCTL0_JR3_GET_FULL_SCALES,&fs);
    printf("Full scales are %d %d %d %d %d %d\n",fs.f[0],fs.f[1],fs.f[2],fs.m[0],fs.m[1],fs.m[2]);
    printf("Setting zero offset...\n");
    ret=ioctl(fd,IOCTL0_JR3_ZEROOFFS);

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



    printf("Set position mode Left Leg");
    posLeftLeg->setPositionMode();
    printf("Set position mode Left Leg");
    posRightLeg->setPositionMode();

    printf("Right Leg positionMove(3,30)\n");
    posRightLeg->positionMove(3, 30);
    printf("Right Leg positionMove(4,-5)\n");
    posRightLeg->positionMove(4,-5);

    Time::delay(2);

    while (1) {
        yarp::os::Bottle bottle;

        ret=ioctl(fd,IOCTL0_JR3_FILTER0,&fm);

        if (ret!=-1) {

            float fz, my, mx;
            printf("[ ");
            for (int i=0;i<3;i++) {
                int f = 100*fm.f[i]*fs.f[i]/16384; // Centesimas de Newton
                fz = 100*fm.f[2]*fs.f[2]/16384;
                printf("%d ",f);
                bottle.addInt(f);
            }
            for (int i=0;i<3;i++) {
                int m = 10*fm.m[i]*fs.m[i]/16384; // Decimas de N·m
                mx = 10*fm.m[0]*fs.m[0]/16384;
                my = 10*fm.m[1]*fs.m[1]/16384;
                printf("%d ",m);
                bottle.addInt(m);
            }

            printf("]\n");

            //printf("--\n");
            //printf("%d\n",(short)fs.v[1]/16384);
            //printf("%d\n",(short)fs.v[2]/16384);

            fz = fz /100; // Newton
            my = my /10; // Newton·metro
            mx = mx/10; // N·m


            // CALCULO ZMP
            if (fz !=0.0){
                xzmp = (float) (-my / fz);
                yzmp = (float) (mx / fz);
            } else{
                xzmp=0;
                yzmp=0;
            }

            cout << "zmp = [ " << xzmp << " , " << yzmp <<" ]" << endl;

            /** EVALUACION MODELO
          **/
            modelo.model(xzmp, yzmp);
            cout << "model ok" << endl;
            //modelo.sendData(port1, data);

            bottle.addDouble(modelo._x1[0]);
            bottle.addDouble(modelo._x2[0]);
            bottle.addDouble(modelo._u);
            bottle.addDouble(modelo._y);

            port.write(bottle);
            cout << "Data sent"<< endl;

            printf("Left Leg positionMove(0,0)\n");
            posLeftLeg->positionMove(0, 0);
            printf("Left Leg positionMove(0,0)\n");
            posLeftLeg->positionMove(1, 0);
            printf("Left Leg positionMove(0,0)\n");
            posLeftLeg->positionMove(2, 0);
            printf("Left Leg positionMove(0,0)\n");
            posLeftLeg->positionMove(3, 0);
            printf("Left Leg positionMove(0,0)\n");
            posLeftLeg->positionMove(4, 0);
            printf("Left Leg positionMove(0,0)\n");
            posLeftLeg->positionMove(5, 0);

        } else perror("");



        //Sample time = 1ms
        usleep(100000); // delay in microseconds
        //sleep(1);
    }
    close(fd);
}

