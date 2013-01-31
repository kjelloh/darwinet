//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFormUnit.h"
#include "ApplicationFormUnit.h"
#include "MIVFormUnit.h"
#include "MessagingFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ViewApplicationActionExecute(TObject *Sender)
{
	TApplicationForm::instance()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ViewMIVActionExecute(TObject *Sender)
{
	TMIVForm::instance()->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ViewMessagingActionExecute(TObject *Sender)
{
	TMessagingForm::instance()->Show();
}
//---------------------------------------------------------------------------

