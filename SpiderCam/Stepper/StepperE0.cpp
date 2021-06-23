/*
 * StepperE0.cpp
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */


#include "StepperE0.h"
StepperE0::StepperE0()
:
	stepperIndex(E0_STEPPER_INDEX)
{
	pinMode(E0_STEP_PIN,   OUTPUT);
	pinMode(E0_DIR_PIN,    OUTPUT);
	pinMode(E0_ENABLE_PIN, OUTPUT);
	digitalWrite(E0_ENABLE_PIN, LOW);


}

StepperE0 StepperE0::getInstance(){
	if(instance==NULL){
		instance=StepperE0();
		stepperVector.push_back(instance);
	}
	return instance;
}
void StepperE0::runStep(){
	E0_STEP_HIGH
	E0_STEP_LOW
}

void StepperE0::setDir(int dir){
	digitalWrite(E0_DIR_PIN, dir);
}

StepperE0::~StepperE0() {
	// TODO Auto-generated destructor stub
}

