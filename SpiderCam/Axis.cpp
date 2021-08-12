/*
 * Axis.cpp
 *
 *  Created on: 29.06.2021
 *      Author: Luisn
 */

#include "Axis.h"
#include "Arduino.h"
#include "PinDefinition.h"
Axis::Axis(Settings setting, int axisIndex) :
		axisIndex(axisIndex),setting(setting),steps(0)

{

	init();
	posStepper=0;
	steps=0;
	updateSetting(setting);

}



int Axis::calculateSteps(Vec3d targetPos) {
	int stepsToMake = ((targetPos - axisPos).getLength() - (increasePerStep * posStepper))
			/ increasePerStep;
	return stepsToMake;
}
void Axis::setStep(int stepsToMake) {
	steps=0;
	setDir(stepsToMake < 0 ? HIGH : LOW);
	stepDir = stepsToMake > 0 ? 1 : -1;
	this->stepsToMake = abs(stepsToMake);
}

void Axis::makeStep() {
	steps++;
	posStepper += stepDir;
	this->executeStep();
}

void Axis::initA() {
	pinMode(X_STEP_PIN, OUTPUT);
	pinMode(X_DIR_PIN, OUTPUT);
	pinMode(X_ENABLE_PIN, OUTPUT);
	digitalWrite(X_ENABLE_PIN, LOW);

}

void Axis::initB() {
	pinMode(Y_STEP_PIN, OUTPUT);
	pinMode(Y_DIR_PIN, OUTPUT);
	pinMode(Y_ENABLE_PIN, OUTPUT);
	digitalWrite(Y_ENABLE_PIN, LOW);
}

void Axis::initC() {
	pinMode(Z_STEP_PIN, OUTPUT);
	pinMode(Z_DIR_PIN, OUTPUT);
	pinMode(Z_ENABLE_PIN, OUTPUT);
	digitalWrite(Z_ENABLE_PIN, LOW);
}

void Axis::initD() {
	pinMode(E0_STEP_PIN, OUTPUT);
	pinMode(E0_DIR_PIN, OUTPUT);
	pinMode(E0_ENABLE_PIN, OUTPUT);
	digitalWrite(E0_ENABLE_PIN, LOW);
}

void Axis::executeStep() {
	switch (axisIndex) {
	case axisIndexA:
		stepA();
		break;
	case axisIndexB:
		stepB();
		break;
	case axisIndexC:
		stepC();
		break;
	case axisIndexD:
		stepD();
		break;
			}
}

void Axis::init() {

	switch (axisIndex) {
		case axisIndexA:
			initA();
			break;
		case axisIndexB:
			initB();
			break;
		case axisIndexC:
			initC();
			break;
		case axisIndexD:
			initD();
			break;
		}
}

void Axis::setDir(int dir) {
	switch (axisIndex) {
	case axisIndexA:
		dirA(dir);
		break;
	case axisIndexB:
		dirB(dir);
		break;
	case axisIndexC:
		dirC(dir);
		break;
	case axisIndexD:
		dirD(dir);
		break;
	}
}

void Axis::updateSetting(Settings setting) {
	winchRadius = setting.winchRadius;
	rotationPerStep = setting.rotationPerStep;
	switch (axisIndex) {
	case axisIndexA:
		axisPos = Vec3d(setting.aAxisSuspension_x, setting.aAxisSuspension_y,
				setting.aAxisSuspension_z);
		break;
	case axisIndexB:
		axisPos = Vec3d(setting.bAxisSuspension_x, setting.bAxisSuspension_y,
				setting.bAxisSuspension_z);
		break;
	case axisIndexC:
		axisPos = Vec3d(setting.cAxisSuspension_x, setting.cAxisSuspension_y,
				setting.cAxisSuspension_z);
		break;
	case axisIndexD:
		axisPos = Vec3d(setting.dAxisSuspension_x, setting.dAxisSuspension_y,
				setting.dAxisSuspension_z);
		break;
	}

	float umfang = 2 * winchRadius * PI;
	increasePerStep = umfang * rotationPerStep;
}

void Axis::stepA() {
	X_STEP_HIGH
	X_STEP_LOW
}
void Axis::stepB() {
	Y_STEP_HIGH
	Y_STEP_LOW
}
void Axis::stepC() {
	Z_STEP_HIGH
	Z_STEP_LOW
}
void Axis::stepD() {
	E0_STEP_HIGH
	E0_STEP_LOW
}

void Axis::dirA(int dir) {
	digitalWrite(X_DIR_PIN, dir);
}
void Axis::dirB(int dir) {
	digitalWrite(Y_DIR_PIN, dir);
}
void Axis::dirC(int dir) {
	digitalWrite(Z_DIR_PIN, dir);
}
void Axis::dirD(int dir) {
	digitalWrite(E0_DIR_PIN, dir);
}
Axis::~Axis() {
	// TODO Auto-generated destructor stub
}


Axis::Axis() {
	Settings setting;
	updateSetting(setting);
	steps=0;
}

int Axis::getDir() {
	return stepDir;
}

int Axis::getSteps(){
	return steps;
}

Vec3d Axis::getPos() {
	return axisPos;
}

void Axis::setPosStepper(int posStepper) {
	this->posStepper=posStepper;
}

int Axis::getPosStepper() {
	return posStepper;
}
