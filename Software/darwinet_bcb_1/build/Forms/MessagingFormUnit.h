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
