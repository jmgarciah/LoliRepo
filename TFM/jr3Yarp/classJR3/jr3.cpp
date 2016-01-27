#include "jr3.h"

JR3::JR3()
{
}

JR3::~JR3(){}

JR3::open(int file_descriptor){
    if ((file_descriptor=open("/dev/jr3",O_RDWR)) < 0) {
        perror("Can't open device. No way to read force!");
       // exit(1);
    }
    return file_descriptor;
}

JR3::getFullScales(int ret, force_array fs){
    ret=ioctl(fd,IOCTL0_JR3_GET_FULL_SCALES,&fs);
    printf("Full scales are %d %d %d %d %d %d\n",fs.f[0],fs.f[1],fs.f[2],fs.m[0],fs.m[1],fs.m[2]);
    return ret;
}

JR3::setZeroOffset(int ret){
     ret=ioctl(fd,IOCTL0_JR3_ZEROOFFS);
     return ret;
}

JR3::read(int ret, int file_descriptor, six_axis_array fm, force_array fs){
    ret=ioctl(file_descriptor,IOCTL0_JR3_FILTER0,&fm);

    if (ret!=-1) {
        fx = 100*fm.f[0]*fs.f[0]/16384;
        fy = 100*fm.f[1]*fs.f[1]/16384;
        fz = 100*fm.f[2]*fs.f[2]/16384;
        mx = 10*fm.m[0]*fs.m[0]/16384;
        my = 10*fm.m[1]*fs.m[1]/16384;
        mz = 10*fm.m[2]*fs.m[2]/16384;

        cout<<"F = [ "<<fx<<" "<<fy<<" "<<fz<<" ]"<<endl;
        cout<<"M = [ "<<mx<<" "<<my<<" "<<mz<<" ]"<<endl;

        _bottle.addInt(fx);
        _bottle.addInt(fy);
        _bottle.addInt(fz);
        _bottle.addInt(mx);
        _bottle.addInt(my);
        _bottle.addInt(mz);

        port.write(_bottle);

    }
}

JR3::zmpPosition(int fz, int mx, int my){
    static float p[2];
    p[0] = -my / fz;
    p[1] = mx / fz;

    return p;
}
