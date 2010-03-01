//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdExplicitTLSClientServerBase"
#pragma link "IdSMTPBase"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	this->NodeComboBox->Items->Add("Node 1");
	this->NodeComboBox->Items->Add("Node 2");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::NodeComboBoxChange(TObject *Sender)
{
	// The user changed the Node Id.
	// TODO: Change to Log In procedure in future generation.


	// Configure us to be selected node
	AnsiString sSelectedNodeId = this->NodeComboBox->Items->operator [](this->NodeComboBox->ItemIndex);

		if (sSelectedNodeId == "Node 1") {
			// Execute SMPT duties
			try {
				this->IdSMTP1->Disconnect(true);

				this->IdSMTP1->QuickSend("mail1.comhem.se","darwinet","n2.darwinet@koh-innovation.se","n1.darwinet@koh-innovation.se","Hello from n1");

			} catch (Exception& e) {
				AnsiString sMessage = "SMTP Exception = ";
				sMessage += e.Message;
				ShowMessage(sMessage);
			}

			// Execute POP3 duties
			try {
				this->IdPOP31->Disconnect(true);
				this->IdPOP31->Host = "mail.koh-innovation.se";
				this->IdPOP31->Password = "2gr64jt";
				this->IdPOP31->Username = "n1.darwinet@koh-innovation.se";

				this->IdPOP31->Connect();

				int noMessages = this->IdPOP31->CheckMessages();
				TIdMessage* pMessage = NULL;
				for (int i = 0; i < noMessages; i++) {
					this->IdPOP31->Retrieve(i,pMessage);
					// Do something with the message
					if (pMessage != NULL) {
						ShowMessage(pMessage->Body->Text);
						delete pMessage;
					}
				}
			} catch (Exception& e) {
				AnsiString sMessage = "POP Exception = ";
				sMessage += e.Message;
				ShowMessage(sMessage);
			}
		}
		else if (sSelectedNodeId == "Node 2") {
			// Execute SMPT duties
			try {
				this->IdSMTP1->Disconnect(true);

				this->IdSMTP1->QuickSend("mail1.comhem.se","darwinet","n1.darwinet@koh-innovation.se","n2.darwinet@koh-innovation.se","Hello from n2");

			} catch (Exception& e) {
				AnsiString sMessage = "SMTP Exception = ";
				sMessage += e.Message;
				ShowMessage(sMessage);
			}

			// Execute POP3 duties
			try {
				this->IdPOP31->Disconnect(true);
				this->IdPOP31->Host = "mail.koh-innovation.se";
				this->IdPOP31->Password = "2gr64jt";
				this->IdPOP31->Username = "n2.darwinet@koh-innovation.se";

				this->IdPOP31->Connect();

				int noMessages = this->IdPOP31->CheckMessages();
				TIdMessage* pMessage = NULL;
				for (int i = 0; i < noMessages; i++) {
					this->IdPOP31->Retrieve(i,pMessage);
					// Do something with the message
					ShowMessage(pMessage->Body->Text);
					delete pMessage;
				}
			} catch (Exception& e) {
				AnsiString sMessage = "POP Exception = ";
				sMessage += e.Message;
				ShowMessage(sMessage);
			}
		}
		this->IdSMTP1->Disconnect(true);
		this->IdPOP31->Disconnect(true);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::IdPOP31Disconnected(TObject *Sender)
{
	// Disconnected from our mailbox
	ShowMessage("POP3 disconnected");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::IdPOP31Status(TObject *ASender,
	  const TIdStatus AStatus, const AnsiString AStatusText)
{
	// Status report from pop3 client
	AnsiString sMessage = "POP3 status, ";
	sMessage += AStatusText;
	ShowMessage(sMessage);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::IdSMTP1Disconnected(TObject *Sender)
{
	ShowMessage("SMTP disconnected");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::IdSMTP1FailedRecipient(TObject *Sender,
	  const AnsiString AAddress, const AnsiString ACode, const AnsiString AText,
	  bool &VContinue)
{

	AnsiString sMessage = "SMTP failed receipient,";
	sMessage += AText;
	ShowMessage(sMessage);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::IdSMTP1Status(TObject *ASender,
	  const TIdStatus AStatus, const AnsiString AStatusText)
{
	AnsiString sMessage = "SMTP status,";
	sMessage += AStatusText;
	ShowMessage(sMessage);
}
//---------------------------------------------------------------------------
