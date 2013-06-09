//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PeerMailFrameUnit.h"
#include "BusinessLogUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPeerMailFrame *PeerMailFrame;
//---------------------------------------------------------------------------
/**
  * Send provided text to Peer mail account
  */
void TPeerMailFrame::send(const String& sMessage) {
	LOG_METHOD_SCOPE;
	try {
//		// Send provided String to Peer mail account
//		String sHost = "smtp01.binero.se";
//		String sSubject = "darwinet delta";
//		String sTo = "darwinet2@itfied.se";
//		String sFrom = "darwinet1@itfied.se";
//		this->IdSMTP1->QuickSend(sHost,sSubject,sTo,sFrom,sMessage);

		if (!this->IdSMTP1->Connected()) {
			if (this->IdSMTP1->SASLMechanisms->Count == 0) {
				// No Simple Access and Secure Layer mechanisms installed. Install one.
				TIdSASLLogin* pIdSASLLogin = new TIdSASLLogin(this->IdSMTP1);
				TIdUserPassProvider* pIdUserPassProvider = new TIdUserPassProvider(pIdSASLLogin);
				pIdUserPassProvider->Username = "darwinet2@itfied.se";
				pIdUserPassProvider->Password = "darw1n3t2";
				pIdSASLLogin->UserPassProvider = pIdUserPassProvider;
				this->IdSMTP1->SASLMechanisms->Add()->SASL = pIdSASLLogin;
			}
			this->IdSMTP1->Connect("smtp.itfied.se",587);
		}

		this->IdMessage1->Subject = "darwinet delta";
		this->IdMessage1->Body->Add("<Darwinet>");
		this->IdMessage1->Body->Add(sMessage);
		this->IdMessage1->Body->Add("</Darwinet>");
		this->IdSMTP1->Send(this->IdMessage1);
	}
	catch (Exception& e) {
		String sMessage(__FUNCTION__" failed. Exception=");
		sMessage += e.Message;
		LOG_DESIGN_INSUFFICIENCY(toLogString(sMessage));
	}
	catch (...) {
		c_LogString sMessage(__FUNCTION__" failed. general Exception cought");
		LOG_DESIGN_INSUFFICIENCY(sMessage);
	}
};
//---------------------------------------------------------------------------
__fastcall TPeerMailFrame::TPeerMailFrame(TComponent* Owner)
	: TFrame(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TPeerMailFrame::IdSMTP1Status(TObject *ASender, const TIdStatus AStatus,
		  const UnicodeString AStatusText)
{
	// Log the status reported by the SMTP component
	String sMessage = "SMTP Status[";
	switch (AStatus) {
		case TIdStatus::hsResolving: sMessage += "hsResolving";break;
		case TIdStatus::hsConnecting: sMessage += "hsConnecting"; break;
		case TIdStatus::hsConnected: sMessage += "hsConnected";break;
		case TIdStatus::hsDisconnecting: sMessage += "hsDisconnecting";break;
		case TIdStatus::hsDisconnected: sMessage += "hsDisconnected";break;
		case TIdStatus::hsStatusText: sMessage += "hsStatusText";break;
		case TIdStatus::ftpTransfer: sMessage += "ftpTransfer";break;
		case TIdStatus::ftpReady: sMessage += "ftpReady";break;
		case TIdStatus::ftpAborted: sMessage += "ftpAborted";break;
	default:
		;
	}
	sMessage += "] \"";
	sMessage += AStatusText;
	sMessage += "\"";
	LOG_DEVELOPMENT_TRACE(toLogString(sMessage));

}
//---------------------------------------------------------------------------

