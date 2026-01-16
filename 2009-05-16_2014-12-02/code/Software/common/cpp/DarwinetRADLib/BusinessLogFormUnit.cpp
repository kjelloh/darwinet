/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
 #ifdef __BCPLUSPLUS__
// RAD Studio XE compilation
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BusinessLogFormUnit.h"
#include "BusinessLogUnit.h"
#include "DataRepresentationFrameWork.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBusinessLogForm *BusinessLogForm = NULL;
//---------------------------------------------------------------------------
/**
  * returns this instance of the form,
  * creating it is if does not yet exist.
  */
TBusinessLogForm* TBusinessLogForm::instance() {
	if (BusinessLogForm == NULL) {
// 120306/KoH, Do not use Application->CreateForm in own code. See https://forums.embarcadero.com/messageview.jspa?messageID=440601&stqc=true
//		Application->CreateForm(__classid(TBusinessLogForm), &BusinessLogForm);
		BusinessLogForm = new TBusinessLogForm(Application->MainForm);
	}
	return BusinessLogForm;
}

//---------------------------------------------------------------------------
/**
  * Docks this form to provided panel
  */
void TBusinessLogForm::DockToPanel(TPanel* panel) {
	// Dock this business log form to provided panel
	this->ManualDock(panel,NULL, alClient);
}

// 120306/KoH. Not used
///**
//  * Start this Log view
//  */
//void TBusinessLogForm::start() {
//	this->PollLogTimer->Enabled = true;
//}

// 120306/KoH. Not used
///**
//  * Stop this Log View
//  */
//void TBusinessLogForm::stop() {
//	this->PollLogTimer->Enabled = false;
//}

//---------------------------------------------------------------------------
__fastcall TBusinessLogForm::TBusinessLogForm(TComponent* Owner)
	: TForm(Owner)
{
	this->PollLogTimer->Enabled = true;

	// Make sure the Business tab is the one shown
	this->LogsPageControl->TabIndex = 0;
}

//---------------------------------------------------------------------------
/**
  * Destructor
  */
__fastcall TBusinessLogForm::~TBusinessLogForm() {
	BusinessLogForm == NULL;
}

//---------------------------------------------------------------------------
void __fastcall TBusinessLogForm::PollLogTimerTimer(TObject *Sender)
{
	static int callCounter = 0;

	for (int i = 0; i < 20; i++) {
		c_BussinessLogEntry* pLogEntry = c_BussinessLoggerIfc::instance()->popUILogEntry();

		if (pLogEntry != NULL) {
			String sMessage = c_DataRepresentationFramework::intToDecimalString(callCounter++,4).c_str();
			sMessage += " ";
			// Convert from UTF8 (Log entry representation) to IDE string
			sMessage += UTF8String(pLogEntry->toString().c_str());
			this->AllRichEdit->Lines->Add(sMessage);

			switch (pLogEntry->getType()) {
				case e_BussinessLogEntryType_DesignInsufficiency:
					this->DesignInsufficiencyLogRichEdit->Lines->Add(sMessage);
				break;
				case e_BussinessLogEntryType_DevelopmentTrace:
					this->DeveloperLogRichEdit->Lines->Add(sMessage);
				break;
				case e_BussinessLogEntryType_Bussiness:
					this->BusinessLogRichEdit->Lines->Add(sMessage);
				break;
			default:
				;
			}

			delete pLogEntry;
		}
		else {
			break;
		}
	}

	if (c_BussinessLoggerIfc::instance()->unPoppedUIEntriesCount() > 0) {
		this->PollLogTimer->Interval = 100;
	}
	else {
		this->PollLogTimer->Interval = 250;
	}
}
//---------------------------------------------------------------------------



#endif // __BCPLUSPLUS__
