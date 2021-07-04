/*
 * SynchronizedTimer.cpp
 *
 *  Created on: 02.07.2021
 *      Author: luisn
 */

#include "SynchronizedTimer.h"
#include <Arduino.h>
const int SynchronizedTimer::timerCount = 4;
const float SynchronizedTimer::movePerTik = 1 / 200;
const float SynchronizedTimer::preScalerCompensation = 1.024;
const int SynchronizedTimer::secInMicroSec = 1000000;
const int SynchronizedTimer::minPeriodLength = 900;
const int SynchronizedTimer::startAccelPeriodLength = 1500;
SynchronizedTimer::SynchronizedTimer() :
		tikTarget(0), tiks(0), nextTikAt(0), stepSize(0), stepThisPeriod(false), interval(
				0) {

}

SynchronizedTimer::~SynchronizedTimer() {
	// TODO Auto-generated destructor stub
}

void SynchronizedTimer::checkTimer() {
	if ((int) nextTikAt == periodCount && tiks < tikTarget) {
		stepThisPeriod = true;
		timerToRun++;
		interval = (nextTikAt - periodCount) * currentPeriodLength;
		nextTikAt += stepSize;
	}
	checkedTimer++;
	if (checkedTimer == timerCount) {
		periodCount++;
		checkedTimer = 0;
	}
}

static void SynchronizedTimer::init() {
	noInterrupts();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;

	OCR1A = 1000;                             // compare value
	TCCR1B |= (1 << WGM12);                   // CTC mode
	TCCR1B |= ((1 << CS11) | (1 << CS10));    // 64 prescaler
	interrupts();
	for (int i = 0; i < timerCount; i++) {
		timerArray[i] = SynchronizedTimer();
	}
}

static int SynchronizedTimer::coordinateTimer() {
	triggeredTimer = 0;
	if (remainingTimer != 0) {
		if (timerToRun == 0) {
			calcPeriodLength();
			for (int i = 0; i < timerCount; i++) {
				timerArray[i].checkTimer();
			}
		}

		if (timerToRun > 0) {
			updateCheckAndTriggerTik();

		}
	}

	checkAndSetTimer();
	return triggeredTimer;
}

static void SynchronizedTimer::updateCheckAndTriggerTik() {
	int lastDelay = OCR1A;
	for (int i = 0; i < timerCount; i++) {
		//Update
		if (timerArray[i].stepThisPeriod) {
			timerArray[i].interval -= lastDelay;
		}
		//CheckandTrigger
		if (timerArray[i].interval <= 0) {
			timerToRun--;
			timerArray[i].stepThisPeriod = false;
			timerArray[i].tiks++;
			triggeredTimer |= 1 << i;
			if (timerArray[i].tiks == timerArray[i].tikTarget) {
				remainingTimer &= ~(1 << i);
			}
		}
	}
}

static int SynchronizedTimer::accelTimer() {
	return currentPeriodLength
			- (2 * currentPeriodLength) / (4 * (++rampUpIndex) + 1);
}

static int SynchronizedTimer::deAccelTimer() {
	isRampingDown = true;
	return (currentPeriodLength * (4 * rampUpIndex + 1))
			/ (4 * (rampUpIndex--) - 1);;
}

static int SynchronizedTimer::calcPeriodLength() {

	if (currentPeriodLength >= startAccelPeriodLength
			&& targetPeriodLength >= startAccelPeriodLength) {
		currentPeriodLength = targetPeriodLength;
	} else if (isRampingDown || tikTarget - tiks > rampUpIndex
			|| targetPeriodLength > currentPeriodLength) {
		currentPeriodLength = deAccelTimer();
		if (currentPeriodLength >= startAccelPeriodLength) {
			currentPeriodLength = startAccelPeriodLength;
			isRampingDown = false;
		}

	} else if (targetPeriodLength < currentPeriodLength) {
		currentPeriodLength = accelTimer();
		if (currentPeriodLength < minPeriodLength) {
			currentPeriodLength = minPeriodLength;
		}
	}
	currentSpeed = (1
			/ ((currentPeriodLength / secInMicroSec) * preScalerCompensation))
			* movePerTik;
	return currentPeriodLength;
}

static void SynchronizedTimer::checkAndSetTimer() {
	if (remainingTimer != 0) {
		int minInterval = 999999;
		for (int i = 0; i < timerCount; i++) {
			if (timerArray[i].stepThisPeriod
					&& timerArray[i].interval < minInterval) {
				minInterval = timerArray[i].interval;
			}
		}
		OCR1A = minInterval;
		TCNT1 = 0;
	}
}

static bool SynchronizedTimer::isRampedDown() {
	return isRampingDown;
}

void SynchronizedTimer::startTimer(float speed, int tiksA, int tiksB, int tiksC,
		int tiksD) {
	targetSpeed = speed;
	targetPeriodLength = secInMicroSec
			/ (speed / (movePerTik / preScalerCompensation));
	targetPeriodLength =
			targetPeriodLength < minPeriodLength ?
					minPeriodLength : targetPeriodLength;

	timerArray[0].tikTarget=tiksA;
	timerArray[1].tikTarget=tiksB;
	timerArray[2].tikTarget=tiksC;
	timerArray[3].tikTarget=tiksD;
	periodCount=0;
	checkedTimer = 0;
	int maxTiks=0;
	for (int i = 0; i < timerCount; i++) {
		maxTiks=timerArray[i].tikTarget > maxTiks?timerArray[i].tikTarget:maxTiks;
	}
	for (int i = 0; i < timerCount; i++) {
		timerArray[i].tiks=0;
		if(timerArray[i].tikTarget>timerArray[i].tiks){
			remainingTimer|=1<<i;
			timerArray[i].stepSize=maxTiks/timerArray[i].tikTarget;
			timerArray[i].nextTikAt=timerArray[i].stepSize;
			timerArray[i].interval=0;
			timerArray[i].stepThisPeriod = false;
		}
	}
}
