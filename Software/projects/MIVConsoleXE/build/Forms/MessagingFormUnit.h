/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef MessagingFormUnitH
#define MessagingFormUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPServer.hpp>
//---------------------------------------------------------------------------
class TMessagingForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *OurIPAndPortEdit;
	TLabel *Label2;
	TEdit *OtherIPAndPortEdit;
	TIdTCPClient *ToOtherPeerTCPClient;
	TIdTCPServer *FromOtherPeerTCPServer;
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations

	/**
	  * Updates the GUI to reflect the currect state
	  */
	void updateGUIToReflectCurrentState();

public:		// User declarations
	__fastcall TMessagingForm(TComponent* Owner);

	/**
	  * Returns the singleton instance of this form.
	  * Creating it if it does not yet exist.
	  */
	static TMessagingForm* instance();

};
//---------------------------------------------------------------------------
extern PACKAGE TMessagingForm *MessagingForm;
//---------------------------------------------------------------------------
#endif
