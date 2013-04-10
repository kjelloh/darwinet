/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */

#ifndef COMMANDLINEPROCESSOR_H_
#define COMMANDLINEPROCESSOR_H_

#include <string>
#include "DarwinetEngineProxy.hpp"

class CommandLineProcessor {
public:
	/**
	 * Constructor
	 */
	CommandLineProcessor();

	/**
	 * Virtual Destructor
	 */
	virtual ~CommandLineProcessor();

	/**
	 * Executes provided Command line.
	 * Returns false if the command was an Exit command
	 */
	bool execute(const std::string& sCommandLine);

private:

	/**
	 * Private storage of our Darwinet Engine Proxy instance
	 */
	DarwinetEngineProxy::shared_ptr m_pDarwinetEngineProxy;

	/**
	 * Returns access to our Darwinet Engine Proxy,
	 * creating it if it does not yet exist.
	 */
	DarwinetEngineProxy::shared_ptr getDarwinetEngineProxy();

};

#endif /* COMMANDLINEPROCESSOR_H_ */
