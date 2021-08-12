/*
 * SynchronizedTimer.h
 *
 *  Created on: 06.07.2021
 *      Author: Luisn
 */

#ifndef SYNCHRONIZEDTIMER_H_
#define SYNCHRONIZEDTIMER_H_

class SynchronizedTimer {
public:
	SynchronizedTimer();
	virtual ~SynchronizedTimer();
public:
	float nextTikAt;
	float stepSize;
	int tikTarget;
	int tiks;
	char tikThisInterval;
	int interval;
	bool done;
public:
	void executeTik();
	char checkTimer(int tik);
	int calcSideInterval(int tik,int tikLength);
	void calcStepSize(int absolutTiks);
	void reset();
	void start(int absolutSteps,int targetSteps);
	void updateInterval(int lastDelay);
	bool isDone();
	bool isTriggered();
	char isTikingThisInterval();
	int getTiks();
	int getInterval() const {
		return interval;
	}
};

#endif /* SYNCHRONIZEDTIMER_H_ */
