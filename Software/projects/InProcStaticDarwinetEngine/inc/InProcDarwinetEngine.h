/*
 * InProcDarwinetEngine.h
 *
 *  Created on: 1 apr 2013
 *      Author: Administrator
 */

#ifndef INPROCDARWINETENGINE_H_
#define INPROCDARWINETENGINE_H_

class InProcDarwinetEngine {
public:

	// A shared pointer to an instance of this class
	typedef InProcDarwinetEngine* shared_ptr;

	InProcDarwinetEngine();
	virtual ~InProcDarwinetEngine();
};

#endif /* INPROCDARWINETENGINE_H_ */
