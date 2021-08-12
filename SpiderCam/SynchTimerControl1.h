/*
 * SynchTimerControll.h
 *
 *  Created on: 07.07.2021
 *      Author: Luisn
 */

#ifndef SYNCHTIMERCONTROL1_H_
#define SYNCHTIMERCONTROL1_H_
#include "PinDefinition.h"
#include "Arduino.h"
#include "SynchronizedTimer.h"
#include "Timerstate1.h"

class SynchTimerControl1 {
public:
	SynchTimerControl1();
	void startTimer(int targetTikInterval,int tikCount[]);
	virtual ~SynchTimerControl1();
	byte tik();
	void setTargetInterval(int targetInterval);
	int getCurrentInterval();
	int getTargetInterval();
	float getProgress();
	void excuteState();
	void accel();
	void decel();
	bool timeToAccel();
	void transitionTo(Timerstate1 *state);
public:

	const float preScalerCompensation=229000/1.024;
	const int minInterval=150;
	const int accelStartInterval=1000;
private:
	Timerstate1* timerState;
	int currentMainInterval;
	int currentSideInterval;
	int targetInterval;
	int tikCount;
	int tikTarget;
	int accelIndex;
	byte childTimerFlag;
	byte isRemainingFlag;
	SynchronizedTimer timerArray[axisNum];
	unsigned short timerIntervalArray[axisNum];
	void setChildTimerFlag();

};

#endif /* SYNCHTIMERCONTROL1_H_ */
