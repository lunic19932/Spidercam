/*
 * StepperY.cpp
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */


#include "StepperY.h"
StepperY::StepperY():
stepperIndex(Y_STEPPER_INDEX)
{
	pinMode(Y_STEP_PIN,   OUTPUT);
	pinMode(Y_DIR_PIN,    OUTPUT);
	pinMode(Y_ENABLE_PIN, OUTPUT);
	digitalWrite(Y_ENABLE_PIN, LOW);


}
StepperY StepperY::getInstance(){
	if(instance==NULL){
		instance=StepperY();
		stepperVector.push_back(instance);
	}
	return instance;
}

void StepperY::runStep(){
	Y_STEP_HIGH
	Y_STEP_LOW
}

void StepperY::setDir(int dir){
	digitalWrite(Y_DIR_PIN, dir);
}

StepperY::~StepperY() {
	// TODO Auto-generated destructor stub
}

