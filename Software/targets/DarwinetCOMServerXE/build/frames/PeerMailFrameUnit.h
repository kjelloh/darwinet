//---------------------------------------------------------------------------

#ifndef PeerMailFrameUnitH
#define PeerMailFrameUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdMessageClient.hpp>
#include <IdSMTP.hpp>
#include <IdSMTPBase.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdMessage.hpp>
#include <IdSASL.hpp>
#include <IdSASLLogin.hpp>
#include <IdSASLUserPass.hpp>
#include <IdUserPassProvider.hpp>
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
class TPeerMailFrame : public TFrame
{
__published:	// IDE-managed Components
	TIdSMTP *IdSMTP1;
	TIdMessage *IdMessage1;
	TIdSASLLogin *IdSASLLogin1;
	TIdUserPassProvider *Darwinet2IdUserPassProvider;
	void __fastcall IdSMTP1Status(TObject *ASender, const TIdStatus AStatus, const UnicodeString AStatusText);

private:	// User declarations

	boost::shared_ptr<TIdSASLLogin> m_pIdSASLLogin;
	boost::shared_ptr<TIdUserPassProvider> m_pIdUserPassProvider;

public:		// User declarations
	__fastcall TPeerMailFrame(TComponent* Owner);

	/**
	  * Send provided text to Peer mail account
	  */
	void send(const String& sMessage);
};
//---------------------------------------------------------------------------
extern PACKAGE TPeerMailFrame *PeerMailFrame;
//---------------------------------------------------------------------------
#endif
