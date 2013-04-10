/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */

#ifndef DARWINETDOMAINPROXY_H_
#define DARWINETDOMAINPROXY_H_

#include "DarwinetViewProxy.hpp"
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
