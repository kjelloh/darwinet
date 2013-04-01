/*
 * DarwinetDomainProxy.h
 *
 *  Created on: 1 apr 2013
 *      Author: Administrator
 */

#ifndef DARWINETDOMAINPROXY_H_
#define DARWINETDOMAINPROXY_H_

#include "DarwinetViewProxy.h"
#include <string>

class DarwinetDomainProxy {
public:

	/**
	 * Shared pointer to DarwinetDomainProxy
	 */
	typedef DarwinetDomainProxy* shared_ptr;

	DarwinetDomainProxy();
	virtual ~DarwinetDomainProxy();

	/**
	 * Returns access to the Proxy to the Darwinet View with provided path (Id),
	 * creating it if it does not yet exist
	 */
	DarwinetViewProxy::shared_ptr getView(const std::string& sViewPath);
private:
	/**
	 * Private storage of our DarwinetViewProxy instance.
	 */
	DarwinetViewProxy::shared_ptr m_pDarwinetViewProxy;

};

#endif /* DARWINETDOMAINPROXY_H_ */
