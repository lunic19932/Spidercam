/*
 * Axis.h
 *
 *  Created on: 29.06.2021
 *      Author: Luisn
 */

#ifndef AXIS_H_
#define AXIS_H_

#include "Vec3d.h"

class Axis {
	private:
	typedef void (*executeStep)();
	typedef void (*setDir)(int dir);
	void stepA();
	void stepB();
	void stepC();
	void stepD();
	void dirA(int dir);
	void dirB(int dir);
	void dirC(int dir);
	void dirD(int dir);
public:
	Axis(Vec3d* currentPos,Vec3d* currentPos,Vec3d axisPos,float winchRadius,float rotationPerStep,executeStep executeStep,setDir);
	virtual ~Axis();
	int calculateSteps();
	void makeStep();
	float getProgress();

private:
	int stepDir;
	int posStepper;
	float winchRadius;
	int increasePerStep;
	float rotationPerStep;
	Vec3d axisPos;
	Vec3d* currentPos;
	Vec3d* targetPos;
	float progress;
	int steps;
	int stepsToMake;
};

#endif /* AXIS_H_ */
