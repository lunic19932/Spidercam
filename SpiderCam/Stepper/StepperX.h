/*
 * StepperX.h
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */

#ifndef STEPPERX_H_
#define STEPPERX_H_

#include "Stepper.h"

class StepperX: public Stepper {
private:
	static StepperX instance;
public:
	virtual ~StepperX();
	void runStep();
	void setDir(int dir);
public:
	static StepperX getInstance();
private:
	StepperX();

};

#endif /* STEPPERX_H_ */
