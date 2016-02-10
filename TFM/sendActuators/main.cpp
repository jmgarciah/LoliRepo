#include <stdio.h>
#include <stdlib.h>

#include "TEO.h"

int main(int argc, char *argv[]) {

    Network yarp;

    TEO teo;

    teo.checkNetwork();
    teo.setOptions(LEFT_ARM);
    teo.setOptions(RIGHT_ARM);
    teo.setMode(LEFT_ARM);
    teo.setMode(RIGHT_ARM);

    teo.sendPosActuators(LEFT_ARM, 0, 5);
    teo.sendPosActuators(LEFT_ARM, 1, -5);
    teo.sendPosActuators(LEFT_ARM, 3, 5);

    Time::delay(1);

    teo.sendPosActuators(RIGHT_ARM, 0, -5);
    teo.sendPosActuators(RIGHT_ARM, 2, -10);

}
