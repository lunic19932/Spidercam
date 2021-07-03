// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _SpiderCam_H_
#define _SpiderCam_H_
#include "Arduino.h"
#include "Vec3d.h"
#include "Axis.h"

void adjustSpeedScales();


class SpiderCam {
public:
	SpiderCam();
	virtual ~SpiderCam();
	void moveToPos(float speed,float x,float y,float z);
	Vec3d getCurrentPos();
	void coordinateMove();

private:
	Vec3d posCurrent,posTarget,posBegin;//Position Cam in mm
	Vec3d moveVector;
	float progressMove;
	Axis axisA,axisB,axisC,axisD;
	byte maxAxisFlag=0;
};
#endif /* _SpiderCam_H_ */

