#include <stdio.h>
#include <stdlib.h>

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

using namespace yarp::os;
using namespace yarp::dev;

int main(int argc, char *argv[]) {

	Network yarp;
	if (!Network::checkNetwork()) {
		printf("Please start a yarp name server first\n");
		return(-1);
	}
	//	Property optionsRightArm;
	//	optionsRightArm.put("device","remote_controlboard");
	//	optionsRightArm.put("remote","/teo/rightArm");
	//	optionsRightArm.put("local","/loli/rightArm");
	//	PolyDriver rightArm(optionsRightArm);
	//	if(!rightArm.isValid()) {
	//		printf("TEO device not available.\n");
	//		rightArm.close();
	//		Network::fini();
	//		return 1;
	//	}
	//
	//	Property optionsLeftArm;
	//	optionsLeftArm.put("device","remote_controlboard");
	//	optionsLeftArm.put("remote","/teo/leftArm");
	//	optionsLeftArm.put("local","/loli/leftArm");
	//	PolyDriver leftArm(optionsLeftArm);
	//	if(!leftArm.isValid()) {
	//		printf("TEO device not available.\n");
	//		leftArm.close();
	//		Network::fini();
	//		return 1;
	//	}

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

	Property optionsLeftLeg;
	optionsLeftLeg.put("device","remote_controlboard");
	optionsLeftLeg.put("remote","/teo/leftArm");
	optionsLeftLeg.put("local","/loli/leftArm");
	PolyDriver leftLeg(optionsLeftLeg);
	if(!leftLeg.isValid()) {
		printf("TEO device not available.\n");
		leftLeg.close();
		Network::fini();
		return 1;
	}

//	IPositionControl *posRightArm;
//	IPositionControl *posLeftArm;
//	bool okRA = rightArm.view(posRightArm);
//	if (!okRA) {
//		printf("[warning] Problems acquiring robot interface\n");
//		return false;
//	} else printf("[success] testTEO acquired robot RightArm inteface\n");
//	posRightArm->setPositionMode();
//
//	bool okLA = leftArm.view(posLeftArm);
//	if (!okLA) {
//		printf("[warning] Problems acquiring robot interface\n");
//		return false;
//	} else printf("[success] testTEO acquired robot LeftArm interface\n");
//	posLeftArm->setPositionMode();
//
//	printf("test Right Arm positionMove(0,10)\n");
//	posRightArm->positionMove(0, 0);
//	printf("test Left Arm positionMove(0,10)\n");
//	posLeftArm->positionMove(0, 0);

	IPositionControl *posRightLeg;
	IPositionControl *posLeftLeg;
	bool okRL = rightLeg.view(posRightLeg);
	if (!okRL) {
		printf("[warning] Problems acquiring robot interface\n");
		return false;
	} else printf("[success] testTEO acquired robot RightArm inteface\n");
	posRightLeg->setPositionMode();

	bool okLL = leftLeg.view(posLeftLeg);
	if (!okLL) {
		printf("[warning] Problems acquiring robot interface\n");
		return false;
	} else printf("[success] testTEO acquired robot LeftArm interface\n");
	posLeftLeg->setPositionMode();

	printf("test Right Arm positionMove(0,10)\n");
	posRightLeg->positionMove(0, 0);
	printf("test Left Arm positionMove(0,10)\n");
	posLeftLeg->positionMove(0, 0);

	printf("Delaying 5 seconds...\n");
	Time::delay(5);

	IEncoders *encRightLeg;
	IEncoders *encLeftLeg;
	okRL = rightLeg.view(encRightLeg);
	okLL = leftLeg.view(encLeftLeg);
	//    IVelocityControl *vel;
	//    ok = dd.view(vel);
	//    vel->setVelocityMode();
	//    printf("test velocityMove(0,10)\n");
	//    vel->velocityMove(0,10);
	//
	//    printf("Delaying 5 seconds...\n");
	//    Time::delay(5);

	return 0;
}
