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
#include "PinDefinition.h"
#include "Settings.h"
#include "SynchTimerControl1.h"

class SpiderCam {
public:
	SpiderCam(float startX, float startY, float startZ, Settings settings);
	virtual ~SpiderCam();
	void moveToPos(float speed, float x, float y, float z);
	Vec3d getCurrentPos();
	Vec3d getTargetPos();
	void coordinateMove();
	Axis* getAxis(int axisIndex);
	void updateSettings(Settings settings);
private:
	void moveToSavedPos();
	void executeMove(int steps[axisNum], float speed, Vec3d target);
	SynchTimerControl1 timerControll;
	Vec3d posCurrent, target, posBegin, savedPos; //Position Cam in mm
	Vec3d moveVector;
	float savedSpeed;
	float speed;
	float progressMove;
	Axis* axis[axisNum];
	Settings settings;
	long time;
	bool waitingForMove;
};
#endif /* _SpiderCam_H_ */

