/*
 * DarwinetEngineProxy.h
 *
 *  Created on: 1 apr 2013
 *      Author: Administrator
 */

#ifndef DARWINETENGINEPROXY_H_
#define DARWINETENGINEPROXY_H_

#include "DarwinetDomainProxy.h"


/**
 * Proxy interface to the Darwinet Engine.
 * The Engine may be in-process or out-of-process. This Proxy interfaces
 * hides this from the caller.
 */
class DarwinetEngineProxy {
public:

	/**
	 * Shared Pointer type
	 */
	typedef DarwinetEngineProxy* shared_ptr;

	DarwinetEngineProxy();
	virtual ~DarwinetEngineProxy();

	/**
	 * Returns access to our Darwinet Domain Proxy instance,
	 * creating it if it does not yet exist.
	 */
	DarwinetDomainProxy::shared_ptr getDomain(const std::string& sDomainPath);

private:
	DarwinetDomainProxy::shared_ptr m_pDarwinetDomainProxy;
};

#endif /* DARWINETENGINEPROXY_H_ */
