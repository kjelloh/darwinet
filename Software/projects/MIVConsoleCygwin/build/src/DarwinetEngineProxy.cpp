/*
 * DarwinetEngineProxy.cpp
 *
 *  Created on: 1 apr 2013
 *      Author: Administrator
 */

#include "DarwinetEngineProxy.h"
#include <iostream> // std::cout

DarwinetEngineProxy::DarwinetEngineProxy()
	: m_pDarwinetDomainProxy(NULL)
{
	// TODO Auto-generated constructor stub

}

DarwinetEngineProxy::~DarwinetEngineProxy() {
	// TODO Auto-generated destructor stub
}

/**
 * Returns access to our Darwinet Domain Proxy instance,
 * creating it if it does not yet exist.
 */
DarwinetDomainProxy::shared_ptr DarwinetEngineProxy::getDomain(const std::string& sDomainPath) {
	if (this->m_pDarwinetDomainProxy == NULL) {
		this->m_pDarwinetDomainProxy = new DarwinetDomainProxy();
	}
	std::string sMessage("DarwinetEngineProxy::getDomain");
	sMessage += " Returning Proxy to Domain \"";
	sMessage += sDomainPath;
	sMessage += "\"";
	std::cout << sMessage << std::endl;
	return this->m_pDarwinetDomainProxy;
}
