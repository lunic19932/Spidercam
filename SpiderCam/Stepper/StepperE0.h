/*
 * StepperE0.h
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */

#ifndef STEPPERE0_H_
#define STEPPERE0_H_

#include "Stepper.h"

class StepperE0:public Stepper{
private:
	static StepperE0 instance;
public:
	virtual ~StepperE0();
	void runStep();
	void setDir(int dir);
public:
	static StepperE0 getInstance();
private:
	StepperE0();

};

#endif /* STEPPERE0_H_ */
