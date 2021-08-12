/*
 * Timerstate.cpp
 *
 *  Created on: 13.08.2021
 *      Author: Luisn
 */

#include "Timerstate1.h"

Timerstate1::Timerstate1():controller(nullptr) {
	// TODO Auto-generated constructor stub

}

Timerstate1::~Timerstate1() {
	// TODO Auto-generated destructor stub
}

void Timerstate1::setController(SynchTimerControl1 *controller) {
	this->controller=controller;
}
