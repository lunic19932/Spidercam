/*
 * StepperE1.cpp
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */


#include "StepperE1.h"
StepperE1::StepperE1():
	stepperIndex(E1_STEPPER_INDEX)
{
	pinMode(E1_STEP_PIN,   OUTPUT);
	pinMode(E1_DIR_PIN,    OUTPUT);
	pinMode(E1_ENABLE_PIN, OUTPUT);
	digitalWrite(E1_ENABLE_PIN, LOW);

}

static StepperE1 StepperE1::getInstance(){
	if(instance==NULL){
		instance=StepperE1();
		stepperVector.push_back(instance);
	}
	return instance;
}
void StepperE1::runStep(){
	E1_STEP_HIGH
	E1_STEP_LOW
}

void StepperE1::setDir(int dir){
	digitalWrite(E1_DIR_PIN, dir);
}

StepperE1::~StepperE1() {
	// TODO Auto-generated destructor stub
}

