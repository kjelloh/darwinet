/*
 * CommandLineProcessor.h
 *
 *  Created on: 1 apr 2013
 *      Author: Administrator
 */

#ifndef COMMANDLINEPROCESSOR_H_
#define COMMANDLINEPROCESSOR_H_

#include <string>

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
};

#endif /* COMMANDLINEPROCESSOR_H_ */
