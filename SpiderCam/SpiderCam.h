// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _SpiderCam_H_
#define _SpiderCam_H_
#include "Arduino.h"
#include "Vec3d.h"
void adjustSpeedScales();

//Do not add code below this line

class SpiderCam {W
public:
	SpiderCam();
	virtual ~SpiderCam();

private:
	float maxSpeedStepper; //Umdrehung pro Sekunde
	float umdrehungPerStep;// Umdrehung pro Schritt
	float winchRadius; //in mm
	Vec3d achseA,achseB,achseC,achseD;//Position Aufhängungen in mm
	Vec3d letztePos,momPos,zielPos;//Position Cam in mm
	int posStepperA,posStepperB,posStepperC,posStepperD;
};
#endif /* _SpiderCam_H_ */

