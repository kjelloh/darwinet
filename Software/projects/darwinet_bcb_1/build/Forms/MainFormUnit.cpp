/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
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

