/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ApplicationFormUnit.h"
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TApplicationForm *ApplicationForm;

//---------------------------------------------------------------------------
TApplicationForm* TApplicationForm::instance() {
	if (ApplicationForm == NULL) {
		ApplicationForm = new TApplicationForm(Application);
	}
	return ApplicationForm;
}

//---------------------------------------------------------------------------
__fastcall TApplicationForm::TApplicationForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TApplicationForm::SpinEdit1Change(TObject *Sender)
{
	this->m_pMIV->setValue(this->SpinEdit1->Value);
}
//---------------------------------------------------------------------------
void __fastcall TApplicationForm::FormCreate(TObject *Sender)
{
	// Get the Domain to use
	this->m_pDomain = darwinet::getDefaultDarwinetDomain();
	// Get a view to the Domain
	this->m_pView = this->m_pDomain->getView();
	// Get the view MIV
	this->m_pMIV = m_pView->getMIV();
}
//---------------------------------------------------------------------------
