#ifndef JR3_H
#define JR3_H

#include <iostream>
#include "jr3pci-ioctl.h"
#include <yarp/os/all.h>

using namespace std;
class JR3
{
public:
    JR3();
    ~JR3();
    int open(int file_descriptor);
    int getFullScales(int ret, force_array fs);
    int setZeroOffset(int ret);
    void read(int ret, int file_descriptor, six_axis_array fm, force_array fs);
    int* zmpPosition(int fz, int mx, int my);

    int fx, fy, fz, mx, my, mz;

private:
    yarp::os::Bottle _bottle;
};

#endif // READJR3_H
