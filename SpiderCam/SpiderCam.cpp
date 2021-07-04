// Do not remove the include below
#include "SpiderCam.h"

#include "PinDefinition.h"
#include "SynchronizedTimer.h"
SpiderCam::SpiderCam():
progressMove(0)
{
	SynchronizedTimer::init();

}

SpiderCam::~SpiderCam() {
	// TODO Auto-generated destructor stub
}

void SpiderCam::moveToPos(float speed, float x, float y, float z) {
	posBegin=posCurrent;
	posTarget = Vec3d(x, y, z);
	moveVector = posTarget - posCurrent;

	axisA.calculateSteps();
	axisB.calculateSteps();
	axisC.calculateSteps();
	axisD.calculateSteps();
}

void SpiderCam::coordinateMove(){



	progressMove=axisA.getProgress()+axisB.getProgress()+axisC.getProgress()+axisD.getProgress()/4;
	posCurrent=posBegin+moveVector.multiply(progressMove);
}

Vec3d SpiderCam::getCurrentPos() {
	return posCurrent;
}

Axis SpiderCam::getAxis(int axisIndex) {
	switch(axisIndex){
	case axisIndexA:
		return axisA;
	case axisIndexB:
		return axisB;
	case axisIndexC:
		return axisC;
	case axisIndexD:
 		return axisD;
	}
	return NULL;
}
