/*
 * Decel.h
 *
 *  Created on: 12.08.2021
 *      Author: Luisn
 */

#ifndef TIMERSTATES_DECEL_H_
#define TIMERSTATES_DECEL_H_

#include "Timerstate1.h"

class Decel: public protected virtual Timerstate1 {
public:
	Decel();
	virtual ~Decel();
	void executeState() override;
	void calcState() override;
};

#endif /* TIMERSTATES_DECEL_H_ */
