#include "TEO.h"

TEO::TEO(){}
TEO::~TEO(){}

int TEO::checkNetwork(){
    if (!Network::checkNetwork()) {
        printf("Please start a yarp name server first\n");
        return(-1);
    } else return 0;
}

int TEO::setOptions(int body_part){
    switch (body_part) {
    case RIGHT_ARM : {
        optionsRightArm.put("device","remote_controlboard");
        optionsRightArm.put("remote","/teo/rightArm");
        optionsRightArm.put("local","/loli/rightArm");

        PolyDriver rightArm(optionsRightArm);
        if(!rightArm.isValid()) {
            printf("TEO device not available.\n");
            rightArm.close();
            Network::fini();
            return 1;
        }

        bool okRA = rightArm.view(posRightArm);
        if (!okRA) {
            printf("[warning] Problems acquiring robot interface\n");
            return false;
        } else printf("[success] testTEO acquired robot RightArm inteface\n");

        return 0;
        break; }

    case LEFT_ARM: {
        optionsLeftArm.put("device","remote_controlboard");
        optionsLeftArm.put("remote","/teo/leftArm");
        optionsLeftArm.put("local","/loli/leftArm");

        PolyDriver leftArm(optionsLeftArm);
        if(!leftArm.isValid()) {
            printf("TEO device not available.\n");
            leftArm.close();
            Network::fini();
            return 1;
        }
        bool okLA = leftArm.view(posLeftArm);
        if (!okLA) {
            printf("[warning] Problems acquiring robot interface\n");
            return false;
        } else printf("[success] testTEO acquired robot LeftArm interface\n");
        return 0;
        break;}

    case RIGHT_LEG:{
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
        bool okRL = rightLeg.view(posRightLeg);
        if (!okRL) {
            printf("[warning] Problems acquiring robot interface\n");
            return false;
        } else printf("[success] testTEO acquired robot RightArm inteface\n");
        return 0;
        break;}

    case LEFT_LEG: {
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
        bool okLL = leftLeg.view(posLeftLeg);
        if (!okLL) {
            printf("[warning] Problems acquiring robot interface\n");
            return false;
        } else printf("[success] testTEO acquired robot LeftArm interface\n");
        return 0;
        break;
    }
    default:
        return -1;
    }
}

bool TEO::setMode(int body_part){

    switch (body_part) {
    case RIGHT_ARM: {
        posRightArm->setPositionMode();
        break;}

    case LEFT_ARM: {
        posLeftArm->setPositionMode();
        break;}

    case RIGHT_LEG:{
        printf("Set position mode Right Leg");
        posRightLeg->setPositionMode();
        break;}

    case LEFT_LEG:{
        printf("Set position mode Left Leg");
        posLeftLeg->setPositionMode();
        break;}

    default:
        break;
    }
}

void TEO::sendPosActuators(int body_part, int joint, float degrees){
    switch (body_part) {
    case RIGHT_ARM: {
        printf("Right Arm positionMove(%d,%f)\n", joint, degrees);
        posRightArm->positionMove(joint, degrees);
        break;}
    case LEFT_ARM:{
        printf("Left Arm positionMove(%d,%f)\n", joint, degrees);
        posLeftArm->positionMove(joint, degrees);
        break;}
    case RIGHT_LEG:{
        printf("Right Leg positionMove(%d,%f)\n", joint, degrees);
        posRightLeg->positionMove(joint, degrees);
        break;}
    case LEFT_LEG:{
        printf("Left Leg positionMove(%d,%f)\n", joint, degrees);
        posLeftLeg->positionMove(joint, degrees);
        break;}
    default:
        break;
    }
}
