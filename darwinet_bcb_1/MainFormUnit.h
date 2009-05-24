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
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Edit1;
	TMenuItem *Help1;
	TMenuItem *About1;
	TListView *TimeAccountListView;
	TEdit *TotalTimeEdit;
	TEdit *ReportTimeEdit;
	TButton *Button1;
	TLabel *Label4;
	TLabel *Label5;
	TIdSMTP *IdSMTP1;
	TIdPOP3 *IdPOP31;
	TComboBox *NodeComboBox;
	TComboBox *UserComboBox;
	void __fastcall NodeComboBoxChange(TObject *Sender);
	void __fastcall IdPOP31Disconnected(TObject *Sender);
	void __fastcall IdPOP31Status(TObject *ASender, const TIdStatus AStatus,
          const AnsiString AStatusText);
	void __fastcall IdSMTP1Disconnected(TObject *Sender);
	void __fastcall IdSMTP1FailedRecipient(TObject *Sender,
          const AnsiString AAddress, const AnsiString ACode,
          const AnsiString AText, bool &VContinue);
	void __fastcall IdSMTP1Status(TObject *ASender, const TIdStatus AStatus,
          const AnsiString AStatusText);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
