 /* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
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
