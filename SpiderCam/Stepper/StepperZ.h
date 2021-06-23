/*
 * StepperZ.h
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */

#ifndef STEPPERZ_H_
#define STEPPERZ_H_

#include "Stepper.h"

class StepperZ: public Stepper {
private:
	static StepperZ instance;
public:
	virtual ~StepperZ();
	void runStep();
	void setDir(int dir);
public:
	static StepperZ getInstance();
private:
	StepperZ();

};

#endif /* STEPPERZ_H_ */
