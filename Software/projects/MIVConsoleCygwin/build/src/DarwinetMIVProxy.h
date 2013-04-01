/*
 * DarwinetMIVProxy.h
 *
 *  Created on: 1 apr 2013
 *      Author: Administrator
 */

#ifndef DARWINETMIVPROXY_H_
#define DARWINETMIVPROXY_H_

#include <string>

class DarwinetMIVProxy {
public:

	/**
	 * Shared pointer to an instance of this class
	 */
	typedef DarwinetMIVProxy* shared_ptr;

	DarwinetMIVProxy();
	virtual ~DarwinetMIVProxy();

	/**
	 * Sets MIV value with provided MIV value path to provided value (represented as a string)
	 */
	void set(const std::string& sValuePath,const std::string& sValue);
};

#endif /* DARWINETMIVPROXY_H_ */
