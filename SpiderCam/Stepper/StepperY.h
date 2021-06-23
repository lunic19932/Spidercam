/*
 * StepperY.h
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */

#ifndef STEPPERY_H_
#define STEPPERY_H_

#include "Stepper.h"

class StepperY: public Stepper {
private:
	static StepperY instance;
public:
	virtual ~StepperY();
	void runStep();
	void setDir(int dir);
public:
	static StepperY getInstance();
private:
	StepperY();

};

#endif /* STEPPERY_H_ */
