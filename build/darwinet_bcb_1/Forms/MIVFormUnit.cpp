//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MIVFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMIVForm *MIVForm;
//---------------------------------------------------------------------------
TMIVForm* TMIVForm::instance() {
	if (MIVForm == NULL) {
		MIVForm = new TMIVForm(Application);
	}
	return MIVForm;
}

//---------------------------------------------------------------------------
__fastcall TMIVForm::TMIVForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
