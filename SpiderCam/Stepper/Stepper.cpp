/*
 * Stepper.cpp
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */

#include "Stepper.h"

Stepper::Stepper():
	acceleration(1000),
	minStepInterval(20),
	startInterval(1000),
	stepPosition(0),
	dir(1),
	totalSteps(0),
	movementDone(true),
	rampUpStepCount(0),
	estStepsToSpeed(0),
	estTimeForMove(0),
	rampUpStepTime(0),
	speedScale(1),
	accIndex(0),
	currentDelay(1000),
	scaledDelay(1000),
	stepCount(0)
{
	stepperVector=std::vector<Stepper>();


}

Stepper::~Stepper() {
}
void Stepper::reset(){
	startInterval = acceleration;
	  currentDelay = startInterval;
	  scaledDelay = currentDelay;
	  stepCount = 0;
	  accIndex = 0;
	  rampUpStepCount = 0;
	  movementDone = false;
	  speedScale = 1;
	  float a = minStepInterval / (float)startInterval;
	  a *= 0.676;
	  float m = ((a*a - 1) / (-2 * a));
	  float n = m * m;
	  estStepsToSpeed = n;
}

float Stepper::getDurationOfAcceleration( unsigned int numSteps) {
  float d = startInterval;
  float totalDuration = 0;
  for (unsigned int n = 1; n < numSteps; n++) {
    d = d - (2 * d) / (4 * n + 1);
    totalDuration += d;
  }
  return totalDuration;
}

void Stepper::prepareMovement(long steps){
	  setDir( steps < 0 ? HIGH : LOW );
	  dir = steps > 0 ? 1 : -1;
	  totalSteps = abs(steps);
	  reset();
	  unsigned long stepsAbs = abs(steps);

	  if ( (2 * estStepsToSpeed) < stepsAbs ) {
	    // there will be a period of time at full speed
	    unsigned long stepsAtFullSpeed = stepsAbs - 2 * estStepsToSpeed;
	    float accelDecelTime = getDurationOfAcceleration( estStepsToSpeed);
	    estTimeForMove = 2 * accelDecelTime + stepsAtFullSpeed * minStepInterval;
	  }
	  else {
	    // will not reach full speed before needing to slow down again
	    float accelDecelTime = getDurationOfAcceleration(  stepsAbs / 2 );
	    estTimeForMove = 2 * accelDecelTime;
	  }
}
static void Stepper::setNextInterruptInterval() {


  unsigned long mind = 999999;
  for (int i = 0; i < stepperVector.size; i++) {
    if ( ((1 << ((Stepper)stepperVector[i]).stepperIndex) & remainingSteppersFlag) && ((Stepper)stepperVector[i]).scaledDelay < mind ) {
      mind = ((Stepper)stepperVector[i]).scaledDelay;
    }
  }

  nextStepperFlag = 0;
  for (int i = 0; i < stepperVector.size; i++) {
    if ( ((1 << ((Stepper)stepperVector[i]).stepperIndex) & remainingSteppersFlag) && ((Stepper)stepperVector[i]).scaledDelay == mind )
      nextStepperFlag |= (1 << ((Stepper)stepperVector[i]).stepperIndex);
  }

  if ( remainingSteppersFlag == 0 ) {
    TIMER1_INTERRUPTS_OFF
    OCR1A = 65500;
  }

  OCR1A = mind;
}

void Stepper::makeStep(){
	runStep();
	if ( stepCount < totalSteps ) {
		      stepCount++;
		      stepPosition += dir;
		      if ( stepCount >= totalSteps ) {
		        movementDone = true;
		        remainingSteppersFlag &= ~(1 << stepperIndex);
		      }
		    }
}
static void Stepper::condinateStepper(){
	unsigned int tmpCtr = OCR1A;

	  OCR1A = 65500;

	  for (int i = 0; i < stepperVector.size; i++) {

	    if ( ! ((1 << ((Stepper)stepperVector[i]).stepperIndex) & remainingSteppersFlag) )
	      continue;

	    if ( ! (nextStepperFlag & (1 << ((Stepper)stepperVector[i]).stepperIndex)) ) {
	    	((Stepper)stepperVector[i]).scaledDelay -= tmpCtr;
	      continue;
	    }

	    Stepper& stepper = stepperVector[i];
	    stepper.makeStep();



	    if ( stepper.rampUpStepCount == 0 ) {
	      stepper.accIndex++;
	      stepper.currentDelay = stepper.currentDelay - (2 * stepper.currentDelay) / (4 * stepper.accIndex + 1);
	      if ( stepper.currentDelay <= stepper.minStepInterval ) {
	        stepper.currentDelay = stepper.minStepInterval;
	        stepper.rampUpStepCount = stepper.stepCount;
	      }
	      if ( stepper.stepCount >= stepper.totalSteps / 2 ) {
	        stepper.rampUpStepCount = stepper.stepCount;
	      }
	      stepper.rampUpStepTime += stepper.currentDelay;
	    }
	    else if ( stepper.stepCount >= stepper.totalSteps - stepper.rampUpStepCount ) {
	      stepper.currentDelay = (stepper.currentDelay * (4 * stepper.accIndex + 1)) / (4 * stepper.accIndex + 1 - 2);
	      stepper.accIndex--;
	    }

	    stepper.scaledDelay = stepper.currentDelay * stepper.speedScale; // integer
	  }

	  setNextInterruptInterval();

	  TCNT1  = 0;
}

static void Stepper::adjustSpeedScales() {
  float maxTime = 0;

  for (int i = 0; i < stepperVector.size; i++) {
    if ( ! ((1 << ((Stepper)stepperVector[i]).stepperIndex) & remainingSteppersFlag) )
      continue;
    volatile Stepper& stepper = stepperVector[i];

    if ( stepper.estTimeForMove > maxTime )
      maxTime = stepper.estTimeForMove;
  }

  if ( maxTime != 0 ) {
    for (int i = 0; i < stepperVector; i++) {
      if ( ! ( (1 << ((Stepper)stepperVector[i]).stepperIndex) & remainingSteppersFlag) )
        continue;
      ((Stepper)stepperVector[i]).speedScale = maxTime / ((Stepper)stepperVector[i]).estTimeForMove;
    }
  }
}

static void Stepper::runMovement(){
	adjustSpeedScales();
	setNextInterruptInterval();
	TIMER1_INTERRUPTS_ON
}
