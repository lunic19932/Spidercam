/*
 * SynchronizedTimer.cpp
 *
 *  Created on: 06.07.2021
 *      Author: Luisn
 */
#include "Arduino.h"
#include "SynchronizedTimer.h"

SynchronizedTimer::SynchronizedTimer() :
		nextTikAt(0), stepSize(0), tikTarget(0), tiks(0), tikThisInterval(
				false), interval(0), done(false) {

}

SynchronizedTimer::~SynchronizedTimer() {
	// TODO Auto-generated destructor stub
}

char SynchronizedTimer::checkTimer(int tik) {
	tikThisInterval = 0;
	if (!done && (int) nextTikAt == tik) {
		tikThisInterval = 1;


	}

	return tikThisInterval;
}

void SynchronizedTimer::calcStepSize(int absolutTiks) {
	stepSize = absolutTiks /(float) tikTarget;
}

void SynchronizedTimer::reset() {
	stepSize = 0;
	nextTikAt = 0;
	tikTarget = 0;
	tiks = 0;
	tikThisInterval = false;
	interval = 0;
	done = true;
}

void SynchronizedTimer::start(int absolutSteps, int targetSteps) {
	reset();
	tikTarget = targetSteps;
	calcStepSize(absolutSteps);
	nextTikAt = 0;
	done = tikTarget == 0;
}

void SynchronizedTimer::executeTik() {
	tikThisInterval = false;
	tiks++;
	nextTikAt += stepSize;
	done = tiks >= tikTarget;
}

void SynchronizedTimer::updateInterval(int lastDelay) {
	if (tikThisInterval) {
		interval -= lastDelay;
	}
}

bool SynchronizedTimer::isDone() {
	return done;
}

bool SynchronizedTimer::isTriggered() {
	return tikThisInterval == 1 && interval <= 0;
}

char SynchronizedTimer::isTikingThisInterval() {
	return tikThisInterval;
}

int SynchronizedTimer::calcSideInterval(int tik, int tikLength) {
	return (nextTikAt - tik) * tikLength;
}

int SynchronizedTimer::getTiks() {
	return tiks;
}
