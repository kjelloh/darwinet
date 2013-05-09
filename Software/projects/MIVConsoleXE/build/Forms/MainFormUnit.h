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
	TAction *ViewApplicationAction;
	TAction *ViewMIVAction;
	TAction *ViewMessagingAction;
	TMenuItem *View1;
	TMenuItem *ViewApplication1;
	TMenuItem *ViewMIV1;
	TMenuItem *ViewMessaging1;
	TGroupBox *EngineGroupBox;
	TGroupBox *DomainGroupBox;
	TButton *DomainConnectButton;
	TButton *EngineConnectButton;
	void __fastcall ViewApplicationActionExecute(TObject *Sender);
	void __fastcall ViewMIVActionExecute(TObject *Sender);
	void __fastcall ViewMessagingActionExecute(TObject *Sender);
	void __fastcall EngineConnectButtonClick(TObject *Sender);
	void __fastcall DomainConnectButtonClick(TObject *Sender);
private:	// User declarations

	/**
	  * Private storage of our Darwinet Engine
	  */
	c_DarwinetEngineProxy::shared_ptr m_pDarwinetEngine;

	/**
	  * Private storage of our darwinet Domain
	  */
	c_DarwinetDomainProxy::shared_ptr m_pDarwinetDomain;

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
