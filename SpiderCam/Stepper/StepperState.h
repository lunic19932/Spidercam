/*
 * StepperState.h
 *
 *  Created on: 23.06.2021
 *      Author: petra
 */

#ifndef STEPPERSTATE_H_
#define STEPPERSTATE_H_

enum StepperState{
	idle,
	changeDirection,
	rampUp,
	maxSpeed,
	rampDown,
	waitForOther
};



#endif /* STEPPERSTATE_H_ */
