/*
 * Axis.h
 *
 *  Created on: 29.06.2021
 *      Author: Luisn
 */

#ifndef AXIS_H_
#define AXIS_H_

#include "Vec3d.h"
#include "Settings.h"

class Axis {
private:
	void executeStep();
	void init();
	void setDir(int dir);
	void stepA();
	void stepB();
	void stepC();
	void stepD();
	void dirA(int dir);
	void dirB(int dir);
	void dirC(int dir);
	void dirD(int dir);
	void initA();
	void initB();
	void initC();
	void initD();
public:
	Axis();
	Axis(Settings setting, int axisIndex);
	virtual ~Axis();
	int calculateSteps(Vec3d target);
	void setStep(int stepsToMake);
	void makeStep();
	void updateSetting(Settings setting);
	int getDir();
	int getSteps();
	Vec3d getPos();
	void setPosStepper(int posStepper);
	int getPosStepper();
private:
	int axisIndex;
	int stepDir;
	int posStepper;
	float winchRadius;
	float increasePerStep;
	float rotationPerStep;
	Settings setting;
	Vec3d axisPos;
	int steps;
	int stepsToMake;
};

#endif /* AXIS_H_ */
