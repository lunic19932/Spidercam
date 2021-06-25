/*
 * Stepper.cpp
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */

#include "Stepper.h"

Stepper::Stepper() :
		acceleration(1000), minStepInterval(20), startInterval(1000), stepPosition(
				0), dir(1), totalSteps(0), stepsToMaxSpeed(0), estTimeForMove(0), rampUpStepTime(0), speedScale(
				1), accIndex(0), currentDelay(1000), scaledDelay(1000), stepCount(
				0), state(idle) {
	stepperVector = std::vector<Stepper>();

}

Stepper::~Stepper() {
}
void Stepper::reset() {
	startInterval = acceleration;
	currentDelay = startInterval; -
	scaledDelay = currentDelay;
	stepCount = 0;
	accIndex = 0;
	speedScale = 1;
	float a = minStepInterval / (float) startInterval;
	a *= 0.676;
	float m = ((a * a - 1) / (-2 * a));
	float n = m * m;
	stepsToMaxSpeed = n;
}

float Stepper::getDurationOfAcceleration(unsigned int numSteps) {
	float d = startInterval;
	float totalDuration = 0;
	for (unsigned int n = 1; n < numSteps; n++) {
		d = d - (2 * d) / (4 * n + 1);
		totalDuration += d;
	}
	return totalDuration;
}

void Stepper::prepareMovement(long steps) {
	setDir(steps < 0 ? HIGH : LOW);
	dir = steps > 0 ? 1 : -1;
	totalSteps = abs(steps);
	reset();
	unsigned long stepsAbs = abs(steps);

	if ((2 * stepsToMaxSpeed) < stepsAbs) {
		// there will be a period of time at full speed
		unsigned long stepsAtFullSpeed = stepsAbs - 2 * stepsToMaxSpeed;
		float accelDecelTime = getDurationOfAcceleration(stepsToMaxSpeed);
		estTimeForMove = 2 * accelDecelTime
				+ stepsAtFullSpeed * minStepInterval;
	} else {
		// will not reach full speed before needing to slow down again
		float accelDecelTime = getDurationOfAcceleration(stepsAbs / 2);
		estTimeForMove = 2 * accelDecelTime;
	}
}
static void Stepper::setNextInterruptInterval() {

	unsigned long mind = 999999;
	if (remainingSteppersFlag == 0) {
			TIMER1_INTERRUPTS_OFF
			OCR1A = 65500;
	}else{
		int nextStepper=-1;
		for (int i = 0; i < stepperVector.size; i++) {
			if (stepperVector[i].state!=waitForOther && stepperVector[i].scaledDelay < mind)
			{
				mind = stepperVector[i].scaledDelay;
				nextStepper=i;
				stepperVector[i].nextStepper=false;
			}
		}
		if(nextStepper>=0){
		stepperVector[nextStepper].nextStepper=true;}

	}
	OCR1A = mind;
}

void Stepper::makeStep() {
	runStep();
	if (stepCount < totalSteps) {
		stepCount++;
		stepPosition += dir;
	}
}

unsigned int Stepper::calculateNextInterval() {
	switch (state) {
	case rampUp:
		accIndex++;
		return currentDelay - (2 * currentDelay) / (4 * accIndex + 1);
	case maxSpeed:
		return minStepInterval;
	case changeDirection:
	case rampDown:
		int delay = (currentDelay * (4 * accIndex + 1))
				/ (4 * accIndex + 1 - 2);
		accIndex--;
		return delay;
	case waitForOther:
	case idle:
	default:
		return startInterval;
	}
}
StepperState Stepper::getCurrentState() {
	switch (state) {
	case idle:
		if (remainingSteppersFlag != 0 && totalSteps>=0)
			return rampUp;
		if(remainingSteppersFlag != 0 && totalSteps==0){
			return waitForOther;
		}
		break;
	case rampUp:
		if (changeDir)
			return changeDirection;
		if (stepCount >= stepsToMaxSpeed)
			return maxSpeed;
		if(stepCount==totalSteps/2)
			return rampDown;
		break;
	case maxSpeed:
		if (changeDir)
			return changeDirection;
		if (stepCount + stepsToStop >= totalSteps)
			return rampDown;

		break;
	case rampDown:
		if (stepCount >= totalSteps){
			remainingSteppersFlag &= ~(1 << stepperIndex);
			return waitForOther;
		}
		break;
	case waitForOther:

		if (remainingSteppersFlag == 0)
			return idle;
		break;
	case changeDirection:
		if (currentDelay >= acceleration)
			return rampUp;
		break;
	default:
		return state;
	}
	return state;
}
static void Stepper::condinateStepper() {
	unsigned int tmpCtr = OCR1A;

	OCR1A = 65500;

	for (int i = 0; i < stepperVector.size; i++) {

		if (stepperVector[i].state==waitForOther)
			continue;

		if (!stepperVector[i].nextStepper) {
			stepperVector[i].scaledDelay -= tmpCtr;
			continue;
		}

		Stepper &stepper = stepperVector[i];
		stepper.makeStep();
		stepper.state = stepper.getCurrentState();
		stepper.currentDelay=stepper.calculateNextInterval();
		stepper.scaledDelay = stepper.currentDelay * stepper.speedScale; // integer
	}

	setNextInterruptInterval();

	TCNT1 = 0;
}

static void Stepper::adjustSpeedScales() {
	float maxTime = 0;

	for (int i = 0; i < stepperVector.size; i++) {
		if (stepperVector[i].state==waitForOther)
			continue;
		Stepper &stepper = stepperVector[i];

		if (stepper.estTimeForMove > maxTime)
			maxTime = stepper.estTimeForMove;
	}

	if (maxTime != 0) {
		for (int i = 0; i < stepperVector; i++) {
			if (stepperVector[i].state==waitForOther)
				continue;
			stepperVector[i].speedScale = maxTime
					/ stepperVector[i].estTimeForMove;
		}
	}
}

static void Stepper::runMovement() {
	adjustSpeedScales();
	setNextInterruptInterval();
	TIMER1_INTERRUPTS_ON
}
