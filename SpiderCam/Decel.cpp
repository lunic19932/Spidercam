/*
 * Decel.cpp
 *
 *  Created on: 12.08.2021
 *      Author: Luisn
 */

#include "Decel.h"
#include "OperatingSlow.h"
#include "Operating.h"
#include "Accel.h"


Decel::Decel() {
	// TODO Auto-generated constructor stub

}

Decel::~Decel() {
	// TODO Auto-generated destructor stub
}

void Decel::executeState() {
	this->controller->decel();
}

void Decel::calcState() {
	if(controller->getCurrentInterval()>=controller->accelStartInterval){
		controller->transitionTo(new OperatingSlow);
	}else if(controller->getCurrentInterval()==controller->getTargetInterval()){
		controller->transitionTo(new Operating);
	}else if(controller->getCurrentInterval()>controller->getTargetInterval()&&controller->timeToAccel()){
		controller->transitionTo(new Accel);
	}
}
