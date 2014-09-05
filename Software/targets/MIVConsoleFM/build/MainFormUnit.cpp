//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MainFormUnit.h"
#include "DarwinetThinkTank.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)

{
	try {
		seedsrc::miv6::test();
	}
	catch (std::runtime_error& e) {
		ShowMessage(e.what());
    }
	catch (...) {
	}
}
//---------------------------------------------------------------------------
