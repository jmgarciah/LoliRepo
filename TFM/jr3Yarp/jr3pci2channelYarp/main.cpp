/*******************************************************
 * main.cpp
 * @Brief: Program for reading forces and torques form two jr3 F/T sensors using jr3pcidriver.
 *      The information read from the sensors is written in a YARP port.
 * @Author: Loli Pinel
 * @Date: September 2015
 *******************************************************/


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include <yarp/os/all.h>

#include "jr3pci-ioctl.h"

//using namespace yarp::os

int main(void) {

    yarp::os::Network yarp;
    yarp::os::Port port0;
    yarp::os::Port port1;
    
    port0.open("/jr3_0:o");
    port1.open("/jr3_1:o");

    six_axis_array fm0, fm1;
    force_array fs0, fs1;
    int ret, fd;
    int i;

    if ((fd=open("/dev/jr3",O_RDWR)) < 0) {
        perror("Can't open device. No way to read force!");
    }
	
    ret=ioctl(fd,IOCTL0_JR3_GET_FULL_SCALES,&fs0);
    printf("Full scales of Sensor 0 are %d %d %d %d %d %d\n",fs0.f[0],fs0.f[1],fs0.f[2],fs0.m[0],fs0.m[1],fs0.m[2]);
    ret=ioctl(fd,IOCTL1_JR3_GET_FULL_SCALES,&fs1);
    printf("Full scales of Sensor 1 are: %d %d %d %d %d %d\n", fs1.f[0],fs1.f[1],fs1.f[2],fs1.m[0],fs1.m[1],fs1.m[2]);
    ret=ioctl(fd,IOCTL0_JR3_ZEROOFFS);
    ret=ioctl(fd,IOCTL1_JR3_ZEROOFFS);


while (1) {
    ret=ioctl(fd,IOCTL0_JR3_FILTER0,&fm0);
    ret=ioctl(fd,IOCTL1_JR3_FILTER0,&fm1);

    if (ret!=-1) {
        yarp::os::Bottle b0, b1;

        // -------- SENSOR 0 ------------ //
        printf("Sensor 0 : [ ");
        for (i=0;i<3;i++) {
            int f0 = 10*fm0.f[i]*fs0.f[i]/16384;
            printf("%d ", f0);
            b0.addInt(f0);
        }

        for (i=0;i<3;i++) {
            int m0 = fm0.m[i]*fs0.m[i]/16384;
            printf("%d ",m0);
            b0.addInt(m0);
        }
        printf("]\n");

        // -------- SENSOR 1 ------------ //
        printf("Sensor 1 : [ ");
        for (i=0;i<3;i++){
            int f1 = 10*fm1.f[i]*fs1.f[i]/16384;
            printf("%d ",f1);
            b1.addInt(f1);
        }
        for (i=0;i<3;i++){
            int m1 = fm1.m[i]*fs1.m[i]/16384;
            printf("%d ",m1);
            b1.addInt(m1);
        }
        printf("]\n");

        port0.write(b0);
        port1.write(b1);
        printf("--\n");

        //printf("%d\n",(short)fs.v[1]/16384);
        //printf("%d\n",(short)fs.v[2]/16384);
    } else perror("");

    usleep(100000);
}
    close(fd);
}


//int main(void){

//    yarp::os::Network yarp;
//    yarp::os::Port port0, port1;

//    port0.open("/jr3_0:o");
//    port1.open("/jr3_1:o");
//    int i=0;
//    int j=0;
//    int k=0;
//    while(true){
//        yarp::os::Bottle b0,b1;

//        b0.addInt(i);
//        b0.addInt(j);
//        b0.addInt(k);
//        b0.addInt(3*i-j);
//        b0.addInt(5*i-2*j+k);
//        b0.addInt(k-1);
//        b1.addInt(2*i);
//        b1.addInt(2*j);
//        b1.addInt(2*k);
//        b1.addInt(3*i);
//        b1.addInt(3*j);
//        b1.addInt(3*k);

//        port0.write(b0);
//        port1.write(b1);

//        std::cout << "i="<<i<<";j="<<j<<std::endl;
//        i++;j++;k++;
//        usleep(10000);
//    }
//}
