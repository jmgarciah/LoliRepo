#include <stdio.h>
#include <stdlib.h>
#include <yarp/os/all.h>
#include <yarp/dev/all.h>

#define RIGHT_ARM 	0
#define LEFT_ARM 	1
#define RIGHT_LEG 	2
#define LEFT_LEG 	3

using namespace yarp::os;
using namespace yarp::dev; 

class TEO {
public:
    TEO();
    ~TEO();
    int checkNetwork();
    int setOptions(int body_part);
    bool setMode(int body_part);
    //void setMode(int extremidad) with position or velocity
    void sendPosActuators(int body_part, int joint, float degrees);
    //void sendVelActuators(int joint, float velocity);

private:
    Property optionsRightArm;
    Property optionsLeftArm;
    Property optionsRightLeg;
	Property optionsLeftLeg;

    IPositionControl *posRightArm;
    IPositionControl *posLeftArm;
    IPositionControl *posRightLeg;
    IPositionControl *posLeftLeg;
};
