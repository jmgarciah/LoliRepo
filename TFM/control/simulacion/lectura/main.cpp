#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include <sys/ioctl.h>

#include <yarp/os/all.h>

#include "jr3pci-ioctl.h"
#include "LIPM2d.h"

using namespace std;

int main(void) {

    yarp::os::Network yarp;
    yarp::os::Port port0;
    yarp::os::Port port1;

    port0.open("/jr3:o");
    port1.open("/system:o");

    yarp::os::Bottle jr3data;
    yarp::os::Bottle bottle;

    six_axis_array fm;
    force_array fs;
    int ret, fd;
    LIPM2d modelo;
    float xzmp = 0;
    float yzmp = 0;

    if ((fd=open("/dev/jr3",O_RDWR)) < 0) {
        perror("Can't open device. No way to read force!");
        // exit(1);
    }

    ret=ioctl(fd,IOCTL0_JR3_GET_FULL_SCALES,&fs);
    printf("Full scales are %d %d %d %d %d %d\n",fs.f[0],fs.f[1],fs.f[2],fs.m[0],fs.m[1],fs.m[2]);
    ret=ioctl(fd,IOCTL0_JR3_ZEROOFFS);

    while (1) {
        ret=ioctl(fd,IOCTL0_JR3_FILTER0,&fm);

        if (ret!=-1) {

            float fz, my, mx;
            printf("[ ");
            for (int i=0;i<3;i++) {
                int f = 100*fm.f[i]*fs.f[i]/16384;
                fz = 100*fm.f[2]*fs.f[2]/16384;
                printf("%d ",f);
                jr3data.addInt(f);
            }
            for (int i=0;i<3;i++) {
                int m = 10*fm.m[i]*fs.m[i]/16384;
                mx = 10*fm.m[0]*fs.m[0]/16384;
                my = 10*fm.m[1]*fs.m[1]/16384;
                printf("%d ",m);
                jr3data.addInt(m);
            }

            printf("]\n");
            port0.write(jr3data);

            //printf("--\n");
            //printf("%d\n",(short)fs.v[1]/16384);
            //printf("%d\n",(short)fs.v[2]/16384);

            fz = fz /100;
            my = my /10;
            mx = mx/10;
            /**
          * CALCULO ZMP
          * ZMPx = -My/Fz
          * ZMPy = Mx/Fz
          **/
            if (fz !=0){
                xzmp = -my / fz;
                yzmp = mx / fz;
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

            bottle.addDouble(modelo._u);
            bottle.addDouble(modelo._x1);
            bottle.addDouble(modelo._x2);
            bottle.addDouble(modelo._y);
            cout << "data bottled" << endl;

            port1.write(bottle);

            cout << "data sent"<< endl;


        } else perror("");



        //Sample time = 1ms
        usleep(100000); // delay in microseconds
        //sleep(1);
    }
    close(fd);
}

