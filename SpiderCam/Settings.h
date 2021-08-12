/*
 * Settings.h
 *
 *  Created on: 04.07.2021
 *      Author: Luisn
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

struct Settings {

	float aAxisSuspension_x = 0;
	float aAxisSuspension_y = 0;
	float aAxisSuspension_z = 62.5;
	float bAxisSuspension_x = 82.5;
	float bAxisSuspension_y = 0;
	float bAxisSuspension_z = 62.5;
	float cAxisSuspension_x = 82.5;
	float cAxisSuspension_y = 26.5;
	float cAxisSuspension_z = 62.5;
	float dAxisSuspension_x = 0;
	float dAxisSuspension_y = 26.5;
	float dAxisSuspension_z = 62.5;
	float maxSpeed = 0.9;
	float winchRadius =  1.6 ;
	float rotationPerStep = 1 / 1600.0;

};

#endif /* SETTINGS_H_ */
