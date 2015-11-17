#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include <yarp/os/all.h>

#include "jr3pci-ioctl.h"

int main(void) {

    yarp::os::Network yarp;
    yarp::os::Port port;
    port.open("/jr3:o");

    six_axis_array fm;
    force_array fs;
    int ret, fd;

    if ((fd=open("/dev/jr3",O_RDWR)) < 0) {
        perror("Can't open device. No way to read force!");
    }
	
    ret=ioctl(fd,IOCTL0_JR3_GET_FULL_SCALES,&fs);
    printf("Full scales are %d %d %d %d %d %d\n",fs.f[0],fs.f[1],fs.f[2],fs.m[0],fs.m[1],fs.m[2]);
    ret=ioctl(fd,IOCTL0_JR3_ZEROOFFS);

while (1) {
    ret=ioctl(fd,IOCTL0_JR3_FILTER0,&fm);

    if (ret!=-1) {
        yarp::os::Bottle b;
        printf("[ ");
        for (int i=0;i<3;i++) {
            int f = 100*fm.f[i]*fs.f[i]/16384;
            printf("%d ",f);
            b.addInt(f);
        }
        for (int i=0;i<3;i++) {
            int m = 10*fm.m[i]*fs.m[i]/16384;
            printf("%d ",m);
            b.addInt(m);
        }
        printf("]\n");
        port.write(b);

        //printf("--\n");
        //printf("%d\n",(short)fs.v[1]/16384);
        //printf("%d\n",(short)fs.v[2]/16384);
    } else perror("");

    //Sample time = 1ms
    usleep(100000); // delay in microseconds
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
//    while(true){
//        yarp::os::Bottle b0,b1;

//        b0.addInt(i);
//        b0.addInt(j);
//        b1.addInt(2*i);
//        b1.addInt(2*j);
//        port0.write(b0);
//        port1.write(b1);

//        std::cout << "i="<<i<<";j="<<j<<std::endl;
//        i++;j++;
//        sleep(1);
//    }
//}
