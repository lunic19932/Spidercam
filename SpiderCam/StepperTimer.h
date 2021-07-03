/*
 * Speedtimer.h
 *
 *  Created on: 29.06.2021
 *      Author: Luisn
 */

#ifndef STEPPERTIMER_H_
#define STEPPERTIMER_H_
#include "StepperState.h"
class StepperTimer {
public:
	StepperTimer();
	virtual ~StepperTimer();
	void setDirRight(bool dir);
	int slowDownDuration();
	void setSpeed(float speed,int steps);
	int getAccelSteps(int intervallA, int intervallB);
private:
	float stepSize;
	bool dirRight;
	int minStartInterval;
	int minInterval;
	int accIndex;
	StepperState state;
	float
private:
	static float speed;
private:
	void calculateTimer();
};

#endif /* STEPPERTIMER_H_ */
