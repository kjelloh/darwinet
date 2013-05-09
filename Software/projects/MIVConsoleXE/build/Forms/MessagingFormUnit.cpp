/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MessagingFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMessagingForm *MessagingForm;
//---------------------------------------------------------------------------
/**
  * Updates the GUI to reflect the currect state
  */
void TMessagingForm::updateGUIToReflectCurrentState() {
	if (GStack != NULL) {
		// Try to use it to get our local IP adress
		static int failureCounter = 0;
		try {
			String sLocalAdress = GStack->LocalAddress;
			sLocalAdress += ":";
			sLocalAdress += this->FromOtherPeerTCPServer->DefaultPort;
			this->OurIPAndPortEdit->Text = sLocalAdress;
			failureCounter = 0;
		}
		catch (...) {
			if (failureCounter++ == 0) {
				// Only log the first failure!
//				LOG_DESIGN_INSUFFICIENCY(_Literalsz("TTestBenchMainForm::updateGUIToReflectChanges failed to get hold of local IP"));
			}
		}
	}
}
//---------------------------------------------------------------------------
/**
  * Returns the singleton instance of this form.
  * Creating it if it does not yet exist.
  */
TMessagingForm* TMessagingForm::instance() {
	if (MessagingForm == NULL) {
		MessagingForm = new TMessagingForm(Application);
	}
	return MessagingForm;
}

//---------------------------------------------------------------------------
__fastcall TMessagingForm::TMessagingForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMessagingForm::FormCreate(TObject *Sender)
{
	this->FromOtherPeerTCPServer->DefaultPort = 4711;
	this->updateGUIToReflectCurrentState();
}
//---------------------------------------------------------------------------
