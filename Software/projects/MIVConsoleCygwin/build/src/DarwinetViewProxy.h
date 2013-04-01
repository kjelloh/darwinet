/*
 * DarwinetViewProxy.h
 *
 *  Created on: 1 apr 2013
 *      Author: Administrator
 */

#ifndef DARWINETVIEWPROXY_H_
#define DARWINETVIEWPROXY_H_

#include "DarwinetMIVProxy.h"

class DarwinetViewProxy {
public:

	/**
	 * Shared pointer to an instance of this class
	 */
	typedef DarwinetViewProxy* shared_ptr;

	DarwinetViewProxy();
	virtual ~DarwinetViewProxy();

	/**
	 * Returns a shared access to our MIV Proxy instance,
	 * creating it if it does not yet exist.
	 */
	DarwinetMIVProxy::shared_ptr getMIV();

private:
	/**
	 * Private storage of our DarwinetMIVProxy instance.
	 */
	DarwinetMIVProxy::shared_ptr m_pDarwinetMIVProxy;
};

#endif /* DARWINETVIEWPROXY_H_ */
