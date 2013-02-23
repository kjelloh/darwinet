/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 * 
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */

#include "stdafx.h"
#include "MIVConsoleCore.h"
#include <string.h>

/**
  * Log a Design Insufficiency into the Application Log manager.
  * A Design Insufficiency is an event to which the executing code has not been dewigned to deal with.
  * Design Insuciciency Logging is the way of the code to "wine" about this.
  * Correctly used Design Insufficiency logging puts a "harness" round the code to detect when business logic needs attention.
  */
void reportDesignInsufficiency(char* szMessage) {
	// TODO: NOT YET IMPLEMENTED.
}

//======================================================================================================
/**
  * Models a delta MIV sequence number
  */
struct t_SequenceNumber {
};

//======================================================================================================
//======================================================================================================
// ** Domain code **

//======================================================================================================
/**
  * Models a Domain in C
  */
struct t_Domain {
};

int reportMIVValueChange(
	t_Domain* pDomain
	,t_SequenceNumber* pSequenceNumber
	,char* szInstanceId
	,char* szDeltaValue) {
	
	// TODO 130223, Distribute the delta to the other nodes of the P2P Domain

	// 1. Get a list of Nodes
	// 2. For each node
		// 2.1 Assemble e message to the node (See "Darwinet P2P Message" in the Darwinet Open P2P Cloud Specification.
		// 2.2 Send the message to the Node
}


// ** Domain Code end **
//======================================================================================================

//======================================================================================================
//**  MIV code **


/**
  * Models a MIV
  */
struct t_MIV {
};

/**
  * Copies the seuqence number of the last delta MIV of provided MIV instance
  * to provided sequence number storage.
  */
void getCurrentSequenceNumber(t_MIV* pMIV,t_SequenceNumber* pSequenceNumber) {
	// TODO 130223
}

/**
  * Returns the value of MIV Value with provided Id in provided MIV instance
  */
char* getMIVValue(t_MIV* pMIV,char* szInstanceId) {
	// TODO 130223
}
/**
  * Sets value with provided Id to provided value in provided MIV instance
  */
// C
bool setMIVValue(t_MIV* pMIV,char* szInstanceId, char* szNewValue) {
	t_SequenceNumber sequence_number;
	getCurrentSequenceNumber(pMIV, &sequence_number);
	char* szCurrentValue = getMIVValue(pMIV,szInstanceId);
	if (strcmp(szCurrentValue, szNewValue) != 0) {
		char szDeltaValue[10] = "4"; // TODO: Process actual change New Value – Current Value and represent as string of decimal digits
		t_Domain* pDomain; // TODO: Get hold of the Domain "we" are viewing into
		int result = reportMIVValueChange(
			 pDomain
			,&sequence_number
			,szInstanceId
			,szDeltaValue);
	}
}

// ** MIV code END **
//======================================================================================================

//======================================================================================================
/**
  * Parse Commands entered at the Console prompt until the Quit command received
  */
void parseConsoleCommands() {

	// Init our view
	t_MIV* pMIV = new t_MIV(); // The MIV instance of this view

	bool doParseAnotherCommand = true;
	while (doParseAnotherCommand) {
		// TODO 130223

		// 1. Read command line command

		// 2. Interpret the Command "SET HelloWorld=4"
		char szInstanceId[20] = "HelloWorld"; // TODO, define by command
		char szNewValue[10] = "4"; // TODO: define by command

		// 3. Call the MIV to set the Value
		if (setMIVValue(pMIV, szInstanceId,szNewValue) == false) {
			reportDesignInsufficiency(getLastError(pMIV));
		}


		// 4. Repeat (Command was not QUIT)

	}
}