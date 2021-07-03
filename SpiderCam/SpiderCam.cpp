// Do not remove the include below
#include "SpiderCam.h"

#include "PinDefinition.h"

SpiderCam::SpiderCam() {
	// TODO Auto-generated constructor stub

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
