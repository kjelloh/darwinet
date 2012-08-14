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
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SpinEdit1Change(TObject *Sender)
{
	// TODO 120808, Update the MIV here

}
//---------------------------------------------------------------------------

