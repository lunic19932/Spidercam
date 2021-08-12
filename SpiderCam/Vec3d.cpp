/*
 * Position.cpp
 *
 *  Created on: 25.06.2021
 *      Author: petra
 */

#include "Vec3d.h"
#include "Arduino.h"

const float Vec3d::tollerance = 0.000000001;
Vec3d::Vec3d() :
		x(0), y(0), z(0) {
}

Vec3d::Vec3d(float x, float y, float z) :
		x(x), y(y), z(z) {
}

Vec3d::~Vec3d() {
}

bool Vec3d::operator==(const Vec3d &otherVec) {
	return x - otherVec.x < tollerance && y - otherVec.y < tollerance
			&& z - otherVec.z < tollerance;
}
Vec3d Vec3d::operator+(const Vec3d &otherVec) {
	return Vec3d(x + otherVec.x, y + otherVec.y, z + otherVec.z);
}
Vec3d Vec3d::operator-(const Vec3d &otherVec) {
	return Vec3d(x - otherVec.x, y - otherVec.y, z - otherVec.z);
}

float Vec3d::getLength() {
	return sqrt(x * x + y * y + z * z);
}

Vec3d Vec3d::div(float div) {
	return Vec3d(x / div, y / div, z / div);
}

Vec3d Vec3d::multiply(float mul) {
	return Vec3d(x * mul, y * mul, z * mul);
}

String Vec3d::toString() {
	String s;
	s += x;
	s += " | ";
	s += y;
	s += " | ";
	s += z;
	return s;
}
