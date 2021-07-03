/*
 * Position.h
 *
 *  Created on: 25.06.2021
 *      Author: petra
 */

#ifndef VEC3D_H_
#define VEC3D_H_

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
private:
	float x,y,z;
	static float tollerance=0.000000001;
};

#endif /* VEC3D_H_ */
