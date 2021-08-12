/*
 * Operating.h
 *
 *  Created on: 12.08.2021
 *      Author: Luisn
 */

#ifndef TIMERSTATES_OPERATING_H_
#define TIMERSTATES_OPERATING_H_

#include "Timerstate1.h"

class Operating: public virtual Timerstate1 {
public:
	Operating();
	virtual ~Operating();
	void executeState() override;
	void calcState() override;
};

#endif /* TIMERSTATES_OPERATING_H_ */
