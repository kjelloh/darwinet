/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */

#ifndef DARWINETVIEWPROXY_H_
#define DARWINETVIEWPROXY_H_

#include "DarwinetMIVProxy.h"

class DarwinetViewProxy {
public:

	/**
	 * Shared pointer to an instance of this class
	 */
	typedef DarwinetViewProxy* shared_ptr;

	DarwinetViewProxy();
	virtual ~DarwinetViewProxy();

	/**
	 * Returns a shared access to our MIV Proxy instance,
	 * creating it if it does not yet exist.
	 */
	DarwinetMIVProxy::shared_ptr getMIV();

private:
	/**
	 * Private storage of our DarwinetMIVProxy instance.
	 */
	DarwinetMIVProxy::shared_ptr m_pDarwinetMIVProxy;
};

#endif /* DARWINETVIEWPROXY_H_ */
