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
private:
	float x,y,z;
};

#endif /* VEC3D_H_ */
