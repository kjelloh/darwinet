/*
 * CommandLineProcessor.h
 *
 *  Created on: 1 apr 2013
 *      Author: Administrator
 */

#ifndef COMMANDLINEPROCESSOR_H_
#define COMMANDLINEPROCESSOR_H_

#include <string>
#include "DarwinetEngineProxy.h"

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
