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
#include "cspin.h"
#include <Vcl.ExtCtrls.hpp>
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
	TGroupBox *SEPSIGroupBox;
	TButton *SEPSIConnectButton;
	TGroupBox *ValuesEditGroupBox;
	TLabel *ValuePathLabel;
	TCSpinEdit *IntValueEdit;
	TSplitter *LogSplitter;
	TPanel *LogPanel;
	void __fastcall EngineConnectButtonClick(TObject *Sender);
	void __fastcall DomainConnectButtonClick(TObject *Sender);
	void __fastcall ViewConnectButtonClick(TObject *Sender);
	void __fastcall SEPSIConnectButtonClick(TObject *Sender);
	void __fastcall IntValueEditChange(TObject *Sender);
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

	/*
	Code Generated When You Import Type Library InformationFrom RAD Studio XE2

	Once you import a type library, you can view the generated TypeLibName_TLB unit. At the top, you will find the following:

	1. First, constant declarations giving symbolic names to the GUIDS of the type library and its interfaces and CoClasses. The names for these constants are generated as follows:

	   * The GUID for the type library has the form LBID_TypeLibName, where TypeLibName is the name of the type library.
	   * The GUID for an interface has the form IID_InterfaceName, where InterfaceName is the name of the interface.
	   * The GUID for a dispinterface has the form DIID_InterfaceName, where InterfaceName is the name of the dispinterface.
	   * The GUID for a CoClass has the form CLASS_ClassName, where ClassName is the name of the CoClass.
	   * The compiler directive VARPROPSETTER will be on. This allows the use of the keyword var in the parameter list of property setter methods.
		 This disables a compiler optimization that would cause parameters to be passed by value instead of by reference.
		 The VARPROPSETTER directive must be on, when creating TLB units for components written in a language other than Delphi.

	2. Second, declarations for the CoClasses in the type library. These map each CoClass to its default interface.

	3. Third, declarations for the interfaces and dispinterfaces in the type library.

	4. Fourth, declarations for a creator class for each CoClass whose default interface supports VTable binding.
	   The creator class has two class methods, Create and CreateRemote, which can be used to instantiate
	   the CoClass locally (Create) or remotely (CreateRemote). These methods return the default interface for the CoClass.

	These declarations provide you with what you need to create instances of the CoClass and access its interface.
	All you need to do is add the generated TypeLibName_TLB.pas file to the uses clause of the unit where you want to bind to a CoClass and call its interfaces.

	Note: This portion of the TypeLibName_TLB unit is also generated when you use the Type Library editor or the command-line utility TLIBIMP.

	If you want to use an ActiveX control, you also need the generated VCL wrapper in addition to the declarations described above.
	The VCL wrapper handles window management issues for the control.
	You may also have generated a VCL wrapper for other CoClasses in the Import Type Library dialog.
	These VCL wrappers simplify the task of creating server objects and calling their methods.
	They are especially recommended if you want your client application to respond to events.

	The declarations for generated VCL wrappers appear at the bottom of the interface section.
	Component wrappers for ActiveX controls are descendants of Vcl.OleCtrls.TOleControl.
	Component wrappers for Automation objects descend from Vcl.OleServer.TOleServer.
	The generated component wrapper adds the properties, events, and methods exposed by the CoClass's interface.
	You can use this component like any other VCL component.

	Warning: You should not edit the generated TypeLibName_TLB unit. It is regenerated each time the type library is refreshed, so any changes will be overwritten.
	Note: For the most up-to-date information about the generated code, refer to the comments in the automatically generated TypeLibName_TLB unit.

	Retrieved from "http://docwiki.embarcadero.com/RADStudio/en/Code_Generated_When_You_Import_Type_Library_Information"
	*/
	// Use COM TLB Objects
	TCOMIDarwinetEngine m_pCOMIDarwinetEngine; // The COM Interface "smart pointer"
	TCOMIDarwinetDomain m_pCOMIDarwinetDomain; // The COM Interface "smart pointer"
	TCOMIDarwinetDomainView m_pCOMIDarwinetDomainView; // The COM Interface "smart pointer"
	TCOMIDarwinetSEPSI m_pCOMIDarwinetSEPSI; // The COM Interface "smart pointer"
	TCOMIDarwinetSEPSIValue m_pCOMIDarwinetSEPSIValue; // The COM Interface "smart pointer"

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
