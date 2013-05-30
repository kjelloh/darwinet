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
#include "BusinessLogUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DarwinetCOMServer_OCX"
#pragma link "DarwinetCOMServer_OCX"
#pragma link "cspin"
#pragma resource "*.dfm"
TMainForm *MainForm;

//---------------------------------------------------------------------------

/**
  * Updates the GUI to reflect any chages that shall be reflected
  * in the GUI
  */
void TMainForm::updateGUIToReflectChanges() {
	bool DarwinetEngineCreated = false;
	bool DarwinetDomainCreated = false;
	bool ViewDomainCreated = false;
	bool SEPSICreated = false;
	switch (m_DarwineEngineWrapperType) {
		case eDarwineEngineWrapperType_Undefined:
			DarwinetEngineCreated = (this->m_pDarwinetEngine); // Enable if the smart pointer referes to an instance
		break;
		case eDarwineEngineWrapperType_Proxy:
		break;
		case eDarwineEngineWrapperType_OCX:
		break;
		case eDarwineEngineWrapperType_TLB:
			DarwinetEngineCreated = (this->m_pCOMIDarwinetEngine); // Enable if the smart pointer refers to an instance
			DarwinetDomainCreated = (this->m_pCOMIDarwinetDomain); // Enable if the smart pointer refers to an instance
			ViewDomainCreated = (this->m_pCOMIDarwinetDomainView); // Enable if the smart pointer refers to an instance
			SEPSICreated = (this->m_pCOMIDarwinetSEPSI); // Enable if the smart pointer refers to an instance
		break;
		case eDarwineEngineWrapperType_Unknown:
		break;
	default:
		;
	}
	this->EngineConnectButton->Caption = (DarwinetEngineCreated?"Close":"Open");
	this->DomainConnectButton->Enabled = DarwinetEngineCreated;
	this->DomainConnectButton->Caption = (DarwinetDomainCreated?"Close":"Open");
	this->ViewConnectButton->Enabled = DarwinetDomainCreated;
	this->ViewConnectButton->Caption = (ViewDomainCreated?"Close":"Open");
	this->SEPSIConnectButton->Enabled = ViewDomainCreated;
	this->SEPSIConnectButton->Caption = (SEPSICreated?"Close":"Open");
	this->ValuePathLabel->Enabled = SEPSICreated;
	this->IntValueEdit->Enabled = SEPSICreated;
}

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
	  ,m_DarwineEngineWrapperType(eDarwineEngineWrapperType_Undefined)
{
//	m_DarwineEngineWrapperType = eDarwineEngineWrapperType_Proxy;
//	m_DarwineEngineWrapperType = eDarwineEngineWrapperType_OCX;
	m_DarwineEngineWrapperType = eDarwineEngineWrapperType_TLB;

	this->updateGUIToReflectChanges();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EngineConnectButtonClick(TObject *Sender)
{

	switch (m_DarwineEngineWrapperType) {
		case eDarwineEngineWrapperType_Undefined:
		break;
		case eDarwineEngineWrapperType_Proxy: {
			// Use Proxy framework (proxy <-> OCX <-> TLB <-> COM Server)
			if (!m_pDarwinetEngine) {
				m_pDarwinetEngine = c_DarwinetEngineFactory::createDarwinetEngine();
			}
			else {
				m_pDarwinetEngine.reset(); // Release our reference the the Engine instance
			}
		}
		break;
		case eDarwineEngineWrapperType_OCX: {
			// Use OCX (COM Interface wrapped into Components)
			static TDarwinetEngine* pDarwinetEngine = NULL;
			if (pDarwinetEngine == NULL) {
				pDarwinetEngine = new TDarwinetEngine(NULL);
				pDarwinetEngine->Connect();
			}
			else {
				pDarwinetEngine->Disconnect();
				delete pDarwinetEngine;
				pDarwinetEngine = NULL;
			}
		}
		break;
		case eDarwineEngineWrapperType_TLB: {
			// Use TLB (COM Interface wrapped into basic objects)
			if (!m_pCOMIDarwinetEngine) {
				m_pCOMIDarwinetEngine = CoDarwinetEngine::Create(); // Use creator method of co class

			}
			else {
				m_pCOMIDarwinetEngine.Release();
			}
		}
		break;
		case eDarwineEngineWrapperType_Unknown:
		break;
	default:
		;
	}
	// Bug in auto-generated code for events. See https://forums.embarcadero.com/message.jspa?messageID=445574&tstart=0
	// See http://www.techvanguards.com

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

	switch (m_DarwineEngineWrapperType) {
		case eDarwineEngineWrapperType_Undefined:
		break;
		case eDarwineEngineWrapperType_Proxy:
			// Use Darwinet Engine Proxies
			if (!m_pDarwinetDomain) {
				m_pDarwinetDomain = m_pDarwinetEngine->getDomain();
			}
			else {
				m_pDarwinetDomain.reset(); // release our reference to the Domain instance
			}
		break;
		case eDarwineEngineWrapperType_OCX:
		break;
		case eDarwineEngineWrapperType_TLB:
			// Use Darwinet Engine TLB
			if (!m_pCOMIDarwinetDomain) {
				m_pCOMIDarwinetDomain = CoDarwinetDomain::Create();
			}
			else {
				m_pCOMIDarwinetDomain.Release();
			}
		break;
		case eDarwineEngineWrapperType_Unknown:
		break;
	default:
		;
	}
	this->updateGUIToReflectChanges();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ViewConnectButtonClick(TObject *Sender)
{
	switch (m_DarwineEngineWrapperType) {
		case eDarwineEngineWrapperType_Undefined:
		break;
		case eDarwineEngineWrapperType_Proxy:
		break;
		case eDarwineEngineWrapperType_OCX:
		break;
		case eDarwineEngineWrapperType_TLB:
			// Use Darwinet Engine TLB
			if (!m_pCOMIDarwinetDomainView) {
				m_pCOMIDarwinetDomainView = CoDarwinetDomainView::Create();
			}
			else {
				m_pCOMIDarwinetDomainView.Release();
			}
		break;
		case eDarwineEngineWrapperType_Unknown:
		break;
	default:
		;
	}

	this->updateGUIToReflectChanges();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SEPSIConnectButtonClick(TObject *Sender)
{
	switch (m_DarwineEngineWrapperType) {
		case eDarwineEngineWrapperType_Undefined:
		break;
		case eDarwineEngineWrapperType_Proxy:
		break;
		case eDarwineEngineWrapperType_OCX:
		break;
		case eDarwineEngineWrapperType_TLB:
			// Use Darwinet Engine TLB
			if (!m_pCOMIDarwinetSEPSI) {
				m_pCOMIDarwinetSEPSI = CoDarwinetSEPSI::Create();
			}
			else {
				m_pCOMIDarwinetSEPSI.Release();
			}
		break;
		case eDarwineEngineWrapperType_Unknown:
		break;
	default:
		;
	}
	this->updateGUIToReflectChanges();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::IntValueEditChange(TObject *Sender)
{
	// Set the SEPSI value to the new one!
	if (m_pCOMIDarwinetSEPSI) {
		// We have a SEPSI instance to talk to!
		String sValuePath = this->ValuePathLabel->Caption;
		String sValue = this->IntValueEdit->Text;
// 130530, This does not yet work. The returned pCOMIDarwinetSEPSIValue is not available beacuse I have not figured out how to marshal it back from teh server.
//		TCOMIDarwinetSEPSIValue pCOMIDarwinetSEPSIValue = m_pCOMIDarwinetSEPSI->getValue(sValuePath.c_str());
//		if (pCOMIDarwinetSEPSIValue) {
//			pCOMIDarwinetSEPSIValue->setTo(sValue.c_str());
//		}
		TCOMIDarwinetSEPSIValue pCOMIDarwinetSEPSIValue = CoDarwinetSEPSIValue::Create();
		if (pCOMIDarwinetSEPSIValue) {
			pCOMIDarwinetSEPSIValue->setTo(sValue.c_str());
		}
	}
}
//---------------------------------------------------------------------------

