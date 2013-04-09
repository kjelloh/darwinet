/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */

#include "DarwinetEngineProxy.h"
#include <iostream> // std::cout
#include "InProcDarwinetEngine.h"

/**
 * Implement one InProcDarwinetEngine as
 * a "singleton" created by the instance() method.
 */
static InProcDarwinetEngine::shared_ptr pInProcDarwinetEngine_instance = NULL;

InProcDarwinetEngine::shared_ptr getInProcDarwinetEngineInstance() {
	if (pInProcDarwinetEngine_instance == NULL) {
		pInProcDarwinetEngine_instance = new InProcDarwinetEngine();
	}
	return pInProcDarwinetEngine_instance;
}

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
