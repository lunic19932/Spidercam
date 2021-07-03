/*
 * Axis.cpp
 *
 *  Created on: 29.06.2021
 *      Author: Luisn
 */

#include "Axis.h"
#include "Arduino.h"
#include "PinDefinition.h"
Axis::Axis(Vec3d* currentPos,Vec3d* targetPos,Vec3d axisPos,float winchRadius,float rotationPerStep,executeStep func,setDir setDir):
	currentPos(currentPos),
	axisPos(axisPos),
	winchRadius(winchRadius),
	posStepper(0),
	increasePerStep(0),
	targetPos(targetPos),
	rotationPerStep(rotationPerStep),
	executeStep(func),
	setDir(setDir)

{
	posStepper=calculateSteps();
	float umfang=2*winchRadius*PI;
	increasePerStep=umfang*rotationPerStep;

}

int Axis::calculateSteps(){
	int stepsToMake= (*targetPos - axisPos - (increasePerStep * posStepper))
			/ increasePerStep;
	setDir( stepsToMake < 0 ? HIGH : LOW);
	stepDir=steps > 0 ? 1 : -1;
	this->stepsToMake=abs(stepsToMake);
	return stepsToMake;
}

void Axis::makeStep(){
	steps++;
	progress=steps/stepsToMake;
	posStepper+=stepDir;
	executeStep();
}

float Axis::getProgress(){
	return progress;
}
void Axis::stepA(){
	X_STEP_HIGH
	X_STEP_LOW
}
void Axis::stepB(){
	Z_STEP_HIGH
	Z_STEP_LOW
}
void Axis::stepC(){
	E0_STEP_HIGH
	E0_STEP_LOW
}
void Axis::stepD(){
	E1_STEP_HIGH
	E1_STEP_LOW
}

void Axis::dirA(int dir){
  digitalWrite(X_DIR_PIN, dir);
}
void Axis::dirB(int dir){
	digitalWrite(Z_DIR_PIN, dir);
}
void Axis::dirC(int dir){
	digitalWrite(E0_DIR_PIN, dir);
}
void Axis::dirD(int dir){
	digitalWrite(E1_DIR_PIN, dir);
}
Axis::~Axis() {
	// TODO Auto-generated destructor stub
}

