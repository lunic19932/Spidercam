/*
 * Position.h
 *
 *  Created on: 25.06.2021
 *      Author: petra
 */

#ifndef VEC3D_H_
#define VEC3D_H_
#include "Arduino.h"
class Vec3d {
public:
	Vec3d();
	Vec3d(float,float,float);
	virtual ~Vec3d();
	bool operator==(const Vec3d& otherVec);
	Vec3d operator+(const Vec3d& otherVec);
	Vec3d operator-(const Vec3d& otherVec);
	float getLength();
	Vec3d div(float div);
	Vec3d multiply(float mul);
	String toString();
private:
	float x,y,z;
	static const float tollerance;
};

#endif /* VEC3D_H_ */
