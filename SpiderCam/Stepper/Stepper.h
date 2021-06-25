/*
 * Stepper.h
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */

#ifndef STEPPER_H_
#define STEPPER_H_
#include "Arduino.h"
#include "PinDefinition.h"
#include "ArduinoSTL.h"
#include "StepperState.h"

class Stepper {
private:
	StepperState getCurrentState();
public:

	Stepper( );
	virtual ~Stepper();

	void reset(void);
	void makeStep(void);
	void prepareMovement(long steps);
	float getDurationOfAcceleration(unsigned int steps);
	void prepareMovement(long steps);
	bool isNextStepper(void);
	unsigned int calculateNextInterval();
public:
	static void condinateStepper(void);
	static void runMovement(void);
public:

	static std::vector<Stepper> stepperVector;
	static volatile byte remainingSteppersFlag=0;
private:
	static void setNextInterruptInterval(void);
	static void adjustSpeedScales(void);
private:
	virtual void runStep(void)=0;
	virtual void setDir(int dir)=0;
protected:
	const int stepperIndex;
private:
	StepperState state;
	float acceleration;
	volatile unsigned long minStepInterval; // ie. max speed, smaller is faster

	// derived parameters
	unsigned int startInterval;                // step interval for first step, determines acceleration
	long stepPosition;              // current position of stepper (total of all movements taken so far)

	// per movement variables (only changed once per movement)
	volatile int dir;                        // current direction of movement, used to keep track of position
	volatile unsigned int totalSteps;        // number of steps requested for current movement
	volatile unsigned long stepsToMaxSpeed;  // estimated steps required to reach max speed
	volatile unsigned long stepsToStop;  // estimated steps required to reach max speed
	volatile unsigned long estTimeForMove;   // estimated time (interrupt ticks) required to complete movement
	volatile unsigned long rampUpStepTime;
	volatile float speedScale;               // used to slow down this motor to make coordinated movement with other motors
	volatile bool changeDir;

	// per iteration variables (potentially changed every interrupt)
	volatile unsigned int accIndex;                 // index in acceleration curve, used to calculate next interval
	volatile float currentDelay;                        // current interval length
	volatile unsigned long scaledDelay;               // above variable truncated
	volatile unsigned int stepCount;         // number of steps completed in current movement
	volatile bool nextStepper;
};


#endif /* STEPPER_H_ */
