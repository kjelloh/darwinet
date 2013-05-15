/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef MainFormUnitH
#define MainFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include "IdExplicitTLSClientServerBase.hpp"
#include "IdSMTPBase.hpp"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdMessageClient.hpp>
#include <IdPOP3.hpp>
#include <IdSMTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPServer.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.OleServer.hpp>
#include "DarwinetEngineProxyFramework.h"
#include "DarwinetCOMServer_OCX.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Edit1;
	TMenuItem *Help1;
	TActionManager *ActionManager1;
	TMenuItem *View1;
	TGroupBox *EngineGroupBox;
	TGroupBox *DomainGroupBox;
	TButton *DomainConnectButton;
	TButton *EngineConnectButton;
	TGroupBox *View;
	TButton *ViewConnectButton;
	TGroupBox *MIVsGroupBox;
	TButton *MIVsConnectButton;
	TGroupBox *ValuesEditGroupBox;
	TEdit *ValueEdit;
	TLabel *ValuePathLabel;
	void __fastcall EngineConnectButtonClick(TObject *Sender);
	void __fastcall DomainConnectButtonClick(TObject *Sender);
	void __fastcall ViewConnectButtonClick(TObject *Sender);
	void __fastcall MIVsConnectButtonClick(TObject *Sender);
	void __fastcall ValueEditChange(TObject *Sender);
private:	// User declarations

	enum e_DarwineEngineWrapperType {
		 eDarwineEngineWrapperType_Undefined
		,eDarwineEngineWrapperType_Proxy
		,eDarwineEngineWrapperType_OCX
		,eDarwineEngineWrapperType_TLB
		,eDarwineEngineWrapperType_Unknown
	};

	e_DarwineEngineWrapperType m_DarwineEngineWrapperType;
	// Use Darwinet Engine Proxies

	/**
	  * Private storage of our Darwinet Engine
	  */
	c_DarwinetEngineProxy::shared_ptr m_pDarwinetEngine;

	/**
	  * Private storage of our darwinet Domain
	  */
	c_DarwinetDomainProxy::shared_ptr m_pDarwinetDomain;

	// Use COM TLB Objects
	TCOMIDarwinetEngine m_pCOMIDarwinetEngine; // The COM Interface "smart pointer"
	TCOMIDarwinetDomain m_pCOMIDarwinetDomain; // The COM Interface "smart pointer"
	TCOMIDarwinetDomainView m_pCOMIDarwinetDomainView; // The COM Interface "smart pointer"
	TCOMIDarwinetMIVs m_pCOMIDarwinetMIVs; // The COM Interface "smart pointer"

	/**
	  * Updates the GUI to reflect any chages that shall be reflected
	  * in the GUI
	  */
	void updateGUIToReflectChanges();

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
