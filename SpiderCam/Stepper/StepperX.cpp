/*
 * StepperX.cpp
 *
 *  Created on: 22.06.2021
 *      Author: petra
 */


#include "StepperX.h"
StepperX::StepperX():
	stepperIndex(X_STEPPER_INDEX)
{
	pinMode(X_STEP_PIN,   OUTPUT);
	pinMode(X_DIR_PIN,    OUTPUT);
	pinMode(X_ENABLE_PIN, OUTPUT);
	digitalWrite(X_ENABLE_PIN, LOW);


}

StepperX StepperX::getInstance(){
	if(instance==NULL){
		instance=StepperX();
		stepperVector.push_back(instance);
	}
	return instance;
}
void StepperX::runStep(){
	X_STEP_HIGH
	X_STEP_LOW
}

void StepperX::setDir(int dir){
	digitalWrite(X_DIR_PIN, dir);
}

StepperX::~StepperX() {
	// TODO Auto-generated destructor stub
}

