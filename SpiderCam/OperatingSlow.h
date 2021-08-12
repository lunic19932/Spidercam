/*
 * OperatingSlow.h
 *
 *  Created on: 12.08.2021
 *      Author: Luisn
 */

#ifndef TIMERSTATES_OPERATINGSLOW_H_
#define TIMERSTATES_OPERATINGSLOW_H_

#include "Timerstate1.h"

class OperatingSlow: public virtual Timerstate1 {
public:
	OperatingSlow();
	virtual ~OperatingSlow();
	void executeState() override;
	void calcState() override;
};

#endif /* TIMERSTATES_OPERATINGSLOW_H_ */
