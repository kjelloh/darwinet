/*
 * DarwinetMIVProxy.cpp
 *
 *  Created on: 1 apr 2013
 *      Author: Administrator
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
