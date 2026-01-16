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
#include "BusinessLogUnit.h"
#include "BusinessLogFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DarwinetCOMServer_OCX"
#pragma link "DarwinetCOMServer_OCX"
#pragma link "cspin"
#pragma resource "*.dfm"
TMainForm *MainForm;

//---------------------------------------------------------------------------
	/*
	When you generate a Component wrapper for an object whose type library you import,
	you can respond to events simply using the events that are added to the generated component.
	If you do not use a Component wrapper, however, (or if the server uses COM+ events), you must write the event sink code yourself.

	Handling Automation events programmatically

	Before you can handle events, you must define an event sink. This is a class that implements the event dispatch interface
	that is defined in the server's type library.

	To write the event sink, create an object that implements the event dispatch interface:

		class MyEventSinkClass: TEventDispatcher<MyEventSinkClass, DIID_TheServerEvents>
		{
		...// declare the methods of DIID_TheServerEvents here
		}

	Once you have an instance of your event sink, you must inform the server object of its existence
	so that the server can call it. To do this, you call the global InterfaceConnect procedure, passing it

	* The interface to the server that generates events.
	* The GUID for the event interface that your event sink handles.
	* An IUnknown interface for your event sink.
	* A variable that receives a Longint that represents the connection between the server and your event sink.

		pInterface = CoServerClassName.CreateRemote("Machine1");
		MyEventSinkClass ES;
		ES.ConnectEvents(pInterface);

	After calling InterfaceConnect, your event sink is connected and receives calls from the server when events occur.

	You must terminate the connection before you free your event sink.
	To do this, call the global InterfaceDisconnect procedure, passing it all the same parameters
	except for the interface to your event sink (and the final parameter is ingoing rather than outgoing):

		ES.DisconnectEvents(pInterface);

	Note: You must be certain that the server has released its connection to your event sink before you free it.
	Because you don't know how the server responds to the disconnect notification initiated by InterfaceDisconnect,
	this may lead to a race condition if you free your event sink immediately after the call.
	The easiest way to guard against problems is to have your event sink maintain its own reference count
	that is not decremented until the server releases the event sink's interface.
	*/

class c_DarwinetSEPSIValueEventsSinkClass : TEventDispatcher<c_DarwinetSEPSIValueEventsSinkClass, &DIID_IDarwinetSEPSIValueEvents> {
public:
	c_DarwinetSEPSIValueEventsSinkClass(TCOMIDarwinetSEPSIValue& pTCOMIDarwinetSEPSIValue) {
		LOG_METHOD_SCOPE;
		this->ConnectEvents(pTCOMIDarwinetSEPSIValue);
	}
protected:
  // To be overriden in derived class to dispatch events
  virtual HRESULT InvokeEvent(DISPID id, TVariant* params = 0) {
	LOG_METHOD_SCOPE;
	return S_OK;
  }
};

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

	// Dock the Business Log form to our main windows
	TBusinessLogForm::instance()->ManualDock(this->LogPanel,NULL,alClient);
	TBusinessLogForm::instance()->Align = alClient;
	TBusinessLogForm::instance()->Visible = true;
	LOG_BUSINESS(_UTF8sz("Application Started!"));

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
				if (m_pCOMIDarwinetSEPSIValue) {
					m_pCOMIDarwinetSEPSIValue.Release();
				}
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
	// Code based on discussion forums reply on https://forums.embarcadero.com/message.jspa?messageID=566825&tstart=0
	try {
		if (!this->m_pCOMIDarwinetSEPSIValue) {
			// String is not compatible with BSTR, have to use WideString instead...
			WideString sValuePath = ValuePathLabel->Caption;
			if (SUCCEEDED(m_pCOMIDarwinetSEPSI->getValue(sValuePath.c_bstr(),&this->m_pCOMIDarwinetSEPSIValue)))
			{
				// Attach our Event sink for this value
				c_DarwinetSEPSIValueEventsSinkClass* pDarwinetSEPSIValueEventsSinkClass(new c_DarwinetSEPSIValueEventsSinkClass(this->m_pCOMIDarwinetSEPSIValue));
			}
			else {
				c_LogString sMessage(__FUNCTION__" failed to get hold of TCOMIDarwinetSEPSIValue instance interface");
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}
		}
		WideString sValue = IntValueEdit->Text;
		this->m_pCOMIDarwinetSEPSIValue->setTo(sValue.c_bstr());
	}
	CATCH_AND_LOG_IDE_STD_AND_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY;
}
//---------------------------------------------------------------------------

