/*
 * SynchronizedTimer.h
 *
 *  Created on: 02.07.2021
 *      Author: luisn
 */

#ifndef SYNCHRONIZEDTIMER_H_
#define SYNCHRONIZEDTIMER_H_

class SynchronizedTimer {
public:
	SynchronizedTimer();
	virtual ~SynchronizedTimer();
	int tikTarget;
	int tiks;
	float nextTikAt;
	float stepSize;
	bool  stepThisPeriod;
	int interval;
	void checkTimer();
public:
	static const int secInMicroSec;
	static const float preScalerCompensation;
	static const float movePerTik;
	static const int timerCount;
	static const int minPeriodLength;
	static const int startAccelPeriodLength;
private:
	static bool isRampingDown;
	static float currentSpeed;
	static float targetSpeed;
	static int rampUpIndex;
	static int targetPeriodLength;
	static int currentPeriodLength;
	static int periodCount;
	static char timerToRun;
	static char triggeredTimer;
	static char checkedTimer;
	static char remainingTimer;
	static SynchronizedTimer timerArray[timerCount];
public:
	static void init();
	static int coordinateTimer();
	static int accelTimer();
	static int deAccelTimer();
	static int calcPeriodLength();
	static void updateCheckAndTriggerTik();
	static void checkAndSetTimer();
	static bool isRampedDown();
	static void startTimer(float speed,int tiksA,int tiksB,int tiksC,int tiksD);
};

#endif /* SYNCHRONIZEDTIMER_H_ */
