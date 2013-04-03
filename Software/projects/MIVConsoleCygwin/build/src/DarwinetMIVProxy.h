/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
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
