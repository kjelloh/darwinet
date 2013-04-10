/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#include "CommandLineProcessor.hpp"
#include <iostream> // std::cout

//---------------------------------------------------------------------------
/**
 * Constructor
 */
CommandLineProcessor::CommandLineProcessor()
	: m_pDarwinetEngineProxy(NULL)
{
	// TODO Auto-generated constructor stub

}

//---------------------------------------------------------------------------
/**
 * Virtual Destructor
 */
CommandLineProcessor::~CommandLineProcessor() {
	// TODO Auto-generated destructor stub
}

//---------------------------------------------------------------------------
/**
 * Executes provided Command line.
 * Returns false if the command was an Exit command.
 */
bool CommandLineProcessor::execute(const std::string& sCommandLine) {
	bool result = false; // default

	// Dummy check for Entered Command
	// TODO: Write actual parser
	if (sCommandLine == "SET") {
		// Hard code "SET HelloWorld = 4"
		this->getDarwinetEngineProxy()->getDomain("Darwinet.MIVConsole")->getView("default")->getMIV()->set("public.HelloWorld","4");
		result = true; // Ok. Remain open for next command
	}
	else if (sCommandLine == "Exit") {
		std::cout << std::endl << ">Thank you and welcome back!" << std::endl;
	}
	else {
		std::string sMessage("Usage: [command] [parameters]\n");
		sMessage += "\n";
		sMessage += "Commands:\n";
		sMessage += "\tSET				;Set a value in the MIV\n";
		sMessage += "\tExit				;Exit this Application\n";
		std::cout << sMessage << std::endl;
		result = true; // Ok. Remain open for next command
	}

	return result;
}

//---------------------------------------------------------------------------
/**
 * Returns access to our Darwinet Engine Proxy,
 * creating it if it does not yet exist.
 */
DarwinetEngineProxy::shared_ptr CommandLineProcessor::getDarwinetEngineProxy() {
	if (this->m_pDarwinetEngineProxy == NULL) {
		this->m_pDarwinetEngineProxy = new DarwinetEngineProxy();
	}
	return this->m_pDarwinetEngineProxy;
}
