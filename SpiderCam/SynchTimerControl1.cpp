/*
 * SynchTimerControll.cpp
 *
 *  Created on: 07.07.2021
 *      Author: Luisn
 */

#include "SynchTimerControl1.h"

#include "Arduino.h"
unsigned short getMinimum(unsigned short array[]) {
	unsigned short min = -1;
	for (int i = 0; i < axisNum; i++) {

		min = min > array[i] ? array[i] : min;
	}
	return min;
}
int getMaximum(int array[]) {
	int max = 0;
	for (int i = 0; i < axisNum; i++) {
		max = max < array[i] ? array[i] : max;
	}
	return max;
}

String getBinaryString(byte inByte) {
	String s;
	for (int b = 7; b >= 0; b--) {
		s += bitRead(inByte, b);
	}
	return s;
}

SynchTimerControl1::SynchTimerControl1() :
		currentMainInterval(accelStartInterval), currentSideInterval(
				accelStartInterval), tikCount(0), tikTarget(0), targetInterval(0), childTimerFlag(0b00000000), accelIndex(
				0) {
	noInterrupts();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 1000;                             // compare value
	TCCR1B |= (1 << WGM12);                   // CTC mode
	TCCR1B |= ((1 << CS11) | (1 << CS10));    // 64 prescaler
	interrupts();
}


void SynchTimerControl1::setTargetInterval(int targetInterval) {
	this->targetInterval = targetInterval;
}

int SynchTimerControl1::getTargetInterval() {
	return targetInterval;
}

void SynchTimerControl1::accel() {
	accelIndex++;

	currentMainInterval = currentMainInterval
			- (2 * currentMainInterval) / (4 * (accelIndex) + 1);
	if (currentMainInterval < targetInterval) {
		currentMainInterval = targetInterval;
	}
	if (currentMainInterval < minInterval) {
		currentMainInterval = minInterval;
	}
}

void SynchTimerControl1::decel() {
	currentMainInterval = (currentMainInterval * (4 * accelIndex + 1))
			/ (4 * (accelIndex) - 1);
	accelIndex--;
	if (currentMainInterval >= accelStartInterval) {
		currentMainInterval = accelStartInterval;
	}
}

bool SynchTimerControl1::timeToAccel() {
	return accelIndex<tikTarget-tikCount;
}

void SynchTimerControl1::setChildTimerFlag() {
	if (!childTimerFlag) {

		excuteState();
		currentSideInterval = currentMainInterval;
		for (int i = 0; i < axisNum; i++) {
			char tikThisInterval = timerArray[i].checkTimer(tikCount);
			childTimerFlag |= tikThisInterval << i;

			if (tikThisInterval != 0) {
				timerIntervalArray[i] = timerArray[i].calcSideInterval(tikCount,
						currentMainInterval);
			} else {
				timerIntervalArray[i] = UINT16_MAX;
			}
		}

	}
}
unsigned long mil;
int k = 0;
byte SynchTimerControl1::tik() {
	setChildTimerFlag();
	String s;

	byte tikFlag = 0;
	unsigned short min = -1;
	int nextInterval = UINT16_MAX;
	if (childTimerFlag != 0b00000000) {
		min = getMinimum(timerIntervalArray);
		currentSideInterval -= min;

		for (int i = 0; i < axisNum; i++) {
			timerIntervalArray[i] -= min;
			if (timerIntervalArray[i] <= 0) {
				tikFlag |= 1 << i;
				childTimerFlag &= ~(1 << i);
				timerArray[i].executeTik();
				timerIntervalArray[i] = UINT16_MAX;
				isRemainingFlag &= ~(((int) timerArray[i].done) << i);
			}
		}
		min = getMinimum(timerIntervalArray);
		if (childTimerFlag == 0b00000000) {
			nextInterval = currentSideInterval;
			tikCount++;
		} else {
			nextInterval = min;

		}

	}
	if (isRemainingFlag == 0b00000000 || getProgress() >= 1) {
		TIMER1_INTERRUPTS_OFF
		Serial.println((millis() - mil) / 1000.0);
	}

	OCR1A = nextInterval;
	TCNT1 = 0;

	return tikFlag;

}



void SynchTimerControl1::startTimer(int targetInterval, int tikCount[]) {
	this->tikCount = 0;
	this->targetInterval =
			targetInterval < minInterval ? minInterval : targetInterval;
	int tikCountAbs[axisNum];
	for (int i = 0; i < axisNum; i++) {
		tikCountAbs[i] = abs(tikCount[i]);
	}
	tikTarget = getMaximum(tikCountAbs);
	excuteState();
	for (int i = 0; i < axisNum; i++) {
		timerArray[i].start(tikTarget, tikCountAbs[i]);
		isRemainingFlag |= (!(int) timerArray[i].done << i);
	}

	OCR1A = currentMainInterval;
	TCNT1 = 0;
	TIMER1_INTERRUPTS_ON
	mil = millis();
}

SynchTimerControl1::~SynchTimerControl1() {
	// TODO Auto-generated destructor stub
}

float SynchTimerControl1::getProgress() {
	return tikCount / (float) tikTarget;
}

void SynchTimerControl1::excuteState() {
	timerState->calcState();
	timerState->executeState();
}

int SynchTimerControl1::getCurrentInterval() {
	return currentMainInterval;
}

void SynchTimerControl1::transitionTo(Timerstate1 *state) {

	if (this->timerState != nullptr)
		delete this->timerState;
	this->timerState = state;
	this->timerState->setController(this);

}
