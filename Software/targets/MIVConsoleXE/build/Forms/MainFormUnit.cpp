/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFormUnit.h"
#include "DarwinetEngineFrameUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DarwinetCOMServer_OCX"
#pragma link "DarwinetCOMServer_OCX"
#pragma resource "*.dfm"
TMainForm *MainForm;

//---------------------------------------------------------------------------

/**
  * Updates the GUI to reflect any chages that shall be reflected
  * in the GUI
  */
void TMainForm::updateGUIToReflectChanges() {
	this->EngineConnectButton->Caption = (this->m_pDarwinetEngine?"Close":"Connect");
}

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------





void __fastcall TMainForm::EngineConnectButtonClick(TObject *Sender)
{

	// Bug in auto-generated code for events. See https://forums.embarcadero.com/message.jspa?messageID=445574&tstart=0
	// See http://www.techvanguards.com

	// Use Proxy framework (proxy <-> OCX <-> TLB <-> COM Server)
	if (!m_pDarwinetEngine) {
		m_pDarwinetEngine = c_DarwinetEngineFactory::createDarwinetEngine();
	}
	else {
		m_pDarwinetEngine.reset(); // Release our reference the the Engine instance
	}

	// Use COM Component directly
//	static TDarwinetEngine* pDarwinetEngine = NULL;
//	if (pDarwinetEngine == NULL) {
//		pDarwinetEngine = new TDarwinetEngine(NULL);
//		pDarwinetEngine->Connect();
//	}
//	else {
//		pDarwinetEngine->Disconnect();
//		delete pDarwinetEngine;
//		pDarwinetEngine = NULL;
//	}

	// Use COM Object directlly
//	static TCOMIDarwinetEngine pCOMIDarwinetEngine; // The COM Interface "smart pointer
//	if (!pCOMIDarwinetEngine) {
//		pCOMIDarwinetEngine = CoDarwinetEngine::Create(); // Use creator method of co class
//
//	}
//	else {
//		pCOMIDarwinetEngine.Release();
//	}

	// Use COM Component in a Frame
//	static TDarwinetEngineFrame* pDarwinetEngineFrame = NULL;
//	if (pDarwinetEngineFrame == NULL) {
//		pDarwinetEngineFrame = new TDarwinetEngineFrame(this);
//	}
//	else {
//		delete pDarwinetEngineFrame;
//		pDarwinetEngineFrame = NULL;
//	}

	this->updateGUIToReflectChanges();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DomainConnectButtonClick(TObject *Sender)
{
	if (!m_pDarwinetDomain) {
		m_pDarwinetDomain = m_pDarwinetEngine->getDomain();
	}
	else {
		m_pDarwinetDomain.reset(); // release our reference to the Domain instance
	}
}
//---------------------------------------------------------------------------

