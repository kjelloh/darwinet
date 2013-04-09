 /* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */

#include "DarwinetMIVProxy.h"
#include <iostream> // std::cout

DarwinetMIVProxy::DarwinetMIVProxy()
{
	// TODO Auto-generated constructor stub

}

DarwinetMIVProxy::~DarwinetMIVProxy() {
	// TODO Auto-generated destructor stub
}

/**
 * Sets MIV value with provided MIV value path to provided value (represented as a string)
 */
void DarwinetMIVProxy::set(const std::string& sValuePath,const std::string& sValue) {
	// TODO: Implement
	std::string sMessage("DarwinetMIVProxy::set");
	sMessage += " Setting MIV value \"";
	sMessage += sValuePath;
	sMessage += "\" to \"";
	sMessage += sValue;
	sMessage += "\"";
	std::cout << sMessage << std::endl;
}
