/*
 * DarwinetViewProxy.cpp
 *
 *  Created on: 1 apr 2013
 *      Author: Administrator
 */

#include "DarwinetViewProxy.h"
#include <iostream> // std::cout

DarwinetViewProxy::DarwinetViewProxy()
	: m_pDarwinetMIVProxy(NULL)
{
	// TODO Auto-generated constructor stub

}

DarwinetViewProxy::~DarwinetViewProxy() {
	// TODO Auto-generated destructor stub
}

/**
 * Returns a shared access to our MIV Proxy instance,
 * creating it if it does not yet exist.
 */
DarwinetMIVProxy::shared_ptr DarwinetViewProxy::getMIV() {
	if (this->m_pDarwinetMIVProxy == NULL) {
		this->m_pDarwinetMIVProxy = new DarwinetMIVProxy();
	}

	std::string sMessage("DarwinetViewProxy::getMIV");
	sMessage += " Returning Proxy to MIV";
	std::cout << sMessage << std::endl;

	return this->m_pDarwinetMIVProxy;
}
