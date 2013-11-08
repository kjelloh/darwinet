//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFormUnit.h"
#include "BusinessLogFormUnit.h"
#include "BusinessLogUnit.h"
#include "SEPSISeed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DarwinetRADLibXE.bpi"

#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	// Dock the Business Log form to our main windows
	TBusinessLogForm::instance()->ManualDock(this,NULL,alClient);
	TBusinessLogForm::instance()->Align = alClient;
	TBusinessLogForm::instance()->Visible = true;
	LOG_BUSINESS(_UTF8sz("Application Started!"));

//	seedsrc::integrate::test();
	seedsrc::integrate2::test();
}
//---------------------------------------------------------------------------
