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

class Stepper {
public:
	Stepper( );
	virtual ~Stepper();

	void reset(void);
	void makeStep(void);
	void prepareMovement(long steps);
	float getDurationOfAcceleration(unsigned int steps);
	void prepareMovement(long steps);
	bool isNextStepper(void);
public:
	static void condinateStepper(void);
	static void runMovement(void);
public:

	static std::vector<Stepper> stepperVector;
	static volatile byte remainingSteppersFlag=0;
	static volatile byte nextStepperFlag=0;
private:
	static void setNextInterruptInterval(void);
	static void adjustSpeedScales(void);
private:
	virtual void runStep(void)=0;
	virtual void setDir(int dir)=0;
protected:
	const int stepperIndex;
private:
	float acceleration;
	volatile unsigned long minStepInterval; // ie. max speed, smaller is faster

	// derived parameters
	unsigned int startInterval;                // step interval for first step, determines acceleration
	long stepPosition;              // current position of stepper (total of all movements taken so far)

	// per movement variables (only changed once per movement)
	volatile int dir;                        // current direction of movement, used to keep track of position
	volatile unsigned int totalSteps;        // number of steps requested for current movement
	volatile bool movementDone;      // true if the current movement has been completed (used by main program to wait for completion)
	volatile unsigned int rampUpStepCount;   // number of steps taken to reach either max speed, or half-way to the goal (will be zero until this number is known)
	volatile unsigned long estStepsToSpeed;  // estimated steps required to reach max speed
	volatile unsigned long estTimeForMove;   // estimated time (interrupt ticks) required to complete movement
	volatile unsigned long rampUpStepTime;
	volatile float speedScale;               // used to slow down this motor to make coordinated movement with other motors

	// per iteration variables (potentially changed every interrupt)
	volatile unsigned int accIndex;                 // index in acceleration curve, used to calculate next interval
	volatile float currentDelay;                        // current interval length
	volatile unsigned long scaledDelay;               // above variable truncated
	volatile unsigned int stepCount;         // number of steps completed in current movement
};


#endif /* STEPPER_H_ */
