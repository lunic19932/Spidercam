/*
 * Timerstate.h
 *
 *  Created on: 13.08.2021
 *      Author: Luisn
 */

#ifndef TIMERSTATE1_H_
#define TIMERSTATE1_H_
#include "SynchTimerControl1.h"
class Timerstate1 {
public:
	Timerstate1();
	virtual ~Timerstate1();
	virtual void executeState()=0;
	virtual void calcState()=0;
	void setController(SynchTimerControl1* controller);
protected:
	SynchTimerControl1* controller;
};

#endif /* TIMERSTATE1_H_ */
