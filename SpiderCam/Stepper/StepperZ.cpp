/*
 * StepperZ.cpp
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */


#include "StepperZ.h"
StepperZ::StepperZ() :
stepperIndex(Z_STEPPER_INDEX)
{
	pinMode(Z_STEP_PIN,   OUTPUT);
	pinMode(Z_DIR_PIN,    OUTPUT);
	pinMode(Z_ENABLE_PIN, OUTPUT);
	digitalWrite(Z_ENABLE_PIN, LOW);


}
StepperZ StepperZ::getInstance(){
	if(instance==NULL){
		instance=StepperZ();
		stepperVector.push_back(instance);
	}
	return instance;
}
void StepperZ::runStep(){
	Z_STEP_HIGH
	Z_STEP_LOW
}

void StepperZ::setDir(int dir){
	digitalWrite(Z_DIR_PIN, dir);
}

StepperZ::~StepperZ() {
	// TODO Auto-generated destructor stub
}

