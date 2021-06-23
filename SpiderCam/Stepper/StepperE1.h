/*
 * StepperE1.h
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */

#ifndef STEPPERE1_H_
#define STEPPERE1_H_

#include "Stepper.h"

class StepperE1: public Stepper {
private:
	static StepperE1 instance;
public:
	virtual ~StepperE1();
	void runStep();
	void setDir(int dir);
public:
	static StepperE1 getInstance();
private:
	StepperE1();
};

#endif /* STEPPERE1_H_ */
