/*
 * DarwinetDomainProxy.cpp
 *
 *  Created on: 1 apr 2013
 *      Author: Administrator
 */

#include "DarwinetDomainProxy.h"
#include <iostream> // std::cout

DarwinetDomainProxy::DarwinetDomainProxy()
	: m_pDarwinetViewProxy(NULL)
{
	// TODO Auto-generated constructor stub

}

DarwinetDomainProxy::~DarwinetDomainProxy() {
	// TODO Auto-generated destructor stub
}

/**
 * Returns access to the Proxy to the Darwinet View with provided path (Id),
 * creating it if it does not yet exist
 */
DarwinetViewProxy::shared_ptr DarwinetDomainProxy::getView(const std::string& sViewPath) {
	if (this->m_pDarwinetViewProxy == NULL) {
		this->m_pDarwinetViewProxy = new DarwinetViewProxy();
	}

	std::string sMessage("DarwinetDomainProxy::getView");
	sMessage += " Returning Proxy to View \"";
	sMessage += sViewPath;
	sMessage += "\"";
	std::cout << sMessage << std::endl;

	return this->m_pDarwinetViewProxy;
}
