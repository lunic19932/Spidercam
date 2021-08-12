/*
 * Accel.h
 *
 *  Created on: 12.08.2021
 *      Author: Luisn
 */

#ifndef TIMERSTATES_ACCEL_H_
#define TIMERSTATES_ACCEL_H_
#include "SynchTimerControl1.h"
#include "Timerstate1.h"
class Accel: public virtual Timerstate1 {
public:
	Accel();
	virtual ~Accel();
	void executeState() override;
	void calcState() override;
};

#endif /* TIMERSTATES_ACCEL_H_ */
