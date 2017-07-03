#include <stdio.h>
#include <stdlib.h>

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

using namespace yarp::os;
using namespace yarp::dev;

int main(int argc, char *argv[]) {

    /** CONNECT YARP NETWORK **/
    Network yarp;
    if (!Network::checkNetwork()) {
        printf("Please start a yarp name server first\n");
        return(-1);
    }

    /** SET CONFIG RIGHT LEG **/
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

    /** SET CONFIG LEFT LEG **/
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

    /** SET POSITION MODE RIGHT LEG **/
    IPositionControl *posRightLeg;
    bool okRL = rightLeg.view(posRightLeg);
    if (!okRL) {
        printf("[warning] Problems acquiring robot interface\n");
        return false;
    } else printf("[success] testTEO acquired robot RightArm inteface\n");
    posRightLeg->setPositionMode();

    /** SET POSITION MODE LEFT LEG **/
    IPositionControl *posLeftLeg;
    bool okLL = leftLeg.view(posLeftLeg);
    if (!okLL) {
        printf("[warning] Problems acquiring robot interface\n");
        return false;
    } else printf("[success] testTEO acquired robot LeftArm interface\n");
    posLeftLeg->setPositionMode();

    /** POSITION CONTROL. RIGHT AND LEFT LEGS**/
    printf("test Right Leg positionMove(4, 0)\n");
    posRightLeg->positionMove(4, 0.0);
    printf("test Left Leg positionMove(4, 0)\n");
    posLeftLeg->positionMove(4, 0.0);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -0.5)\n");
    posRightLeg->positionMove(4, -0.5);
    printf("test Left Leg positionMove(4, -0.5)\n");
    posLeftLeg->positionMove(4, -0.5);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -1.0)\n");
    posRightLeg->positionMove(4, -1.0);
    printf("test Left Leg positionMove(4, -1.0)\n");
    posLeftLeg->positionMove(4, -1.0);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -1.5)\n");
    posRightLeg->positionMove(4, -1.5);
    printf("test Left Leg positionMove(4, -1.5)\n");
    posLeftLeg->positionMove(4, -1.5);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -2.0)\n");
    posRightLeg->positionMove(4, -2.0);
    printf("test Left Leg positionMove(4, -2.0)\n");
    posLeftLeg->positionMove(4, -2.0);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -2.5)\n");
    posRightLeg->positionMove(4, -2.5);
    printf("test Left Leg positionMove(4, -2.5)\n");
    posLeftLeg->positionMove(4, -2.5);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -3.0)\n");
    posRightLeg->positionMove(4, -3.0);
    printf("test Left Leg positionMove(4, -3.0)\n");
    posLeftLeg->positionMove(4, -3.0);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -3.5)\n");
    posRightLeg->positionMove(4, -3.5);
    printf("test Left Leg positionMove(4, -3.5)\n");
    posLeftLeg->positionMove(4, -3.5);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -4.0)\n");
    posRightLeg->positionMove(4, -4.0);
    printf("test Left Leg positionMove(4, -4.0)\n");
    posLeftLeg->positionMove(4, -4.0);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -4.5)\n");
    posRightLeg->positionMove(4, -4.5);
    printf("test Left Leg positionMove(4, -4.5)\n");
    posLeftLeg->positionMove(4, -4.5);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -5.0)\n");
    posRightLeg->positionMove(4, -5.0);
    printf("test Left Leg positionMove(4, -5.0)\n");
    posLeftLeg->positionMove(4, -5.0);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -5.5)\n");
    posRightLeg->positionMove(4, -5.5);
    printf("test Left Leg positionMove(4, -5.5)\n");
    posLeftLeg->positionMove(4, -5.5);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -6.0)\n");
    posRightLeg->positionMove(4, -6.0);
    printf("test Left Leg positionMove(4, -6.0)\n");
    posLeftLeg->positionMove(4, -6.0);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -6.5)\n");
    posRightLeg->positionMove(4, -6.5);
    printf("test Left Leg positionMove(4, -6.5)\n");
    posLeftLeg->positionMove(4, -6.5);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -7.0)\n");
    posRightLeg->positionMove(4, -7.0);
    printf("test Left Leg positionMove(4, -7.0)\n");
    posLeftLeg->positionMove(4, -7.0);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -7.5)\n");
    posRightLeg->positionMove(4, -7.5);
    printf("test Left Leg positionMove(4, -7.5)\n");
    posLeftLeg->positionMove(4, -7.5);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -8.0)\n");
    posRightLeg->positionMove(4, -8.0);
    printf("test Left Leg positionMove(4, -8.0)\n");
    posLeftLeg->positionMove(4, -8.0);
    Time::delay(15);

/*    printf("test Right Leg positionMove(4, -8.5)\n");
    posRightLeg->positionMove(4, -8.5);
    printf("test Left Leg positionMove(4, -8.5)\n");
    posLeftLeg->positionMove(4, -8.5);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -9.0)\n");
    posRightLeg->positionMove(4, -9.0);
    printf("test Left Leg positionMove(4, -9.0)\n");
    posLeftLeg->positionMove(4, -9.0);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -9.5)\n");
    posRightLeg->positionMove(4, -9.5);
    printf("test Left Leg positionMove(4, -9.5)\n");
    posLeftLeg->positionMove(4, -9.5);
    Time::delay(15);

    printf("test Right Leg positionMove(4, -10.0)\n");
    posRightLeg->positionMove(4, -10.0);
    printf("test Left Leg positionMove(4, -10.0)\n");
    posLeftLeg->positionMove(4, -10.0);
    Time::delay(15);*/

    return 0;
}
