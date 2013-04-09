/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
 #ifdef __BCPLUSPLUS__
// RAD Studio XE compilation
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EditPropertiesFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditPropertiesForm *EditPropertiesForm = NULL;
//---------------------------------------------------------------------------

// Removed 111205/KoH
///**
//  * returns this singleton, creating it if it does not yet exist
//  */
//TEditPropertiesForm* TEditPropertiesForm::instance() {
//	if (EditPropertiesForm == NULL) {
//		Application->CreateForm(__classid(TEditPropertiesForm), &EditPropertiesForm);
//	}
//	return EditPropertiesForm;
//}

//---------------------------------------------------------------------------
__fastcall TEditPropertiesForm::TEditPropertiesForm(TComponent* Owner,TEditApplicationPropertiesFrame* pEditApplicationPropertiesFrame)
	:  TForm(Owner)
//	  ,m_pEditApplicationPropertiesFrame(new TEditApplicationPropertiesFrame(this))
	  ,m_pEditApplicationPropertiesFrame(pEditApplicationPropertiesFrame)
{
	m_pEditApplicationPropertiesFrame->Align = alClient;
	m_pEditApplicationPropertiesFrame->Parent = Panel1;
}
//---------------------------------------------------------------------------

/**
  * Executes this dialog with provided StringList
  */
bool TEditPropertiesForm::Execute(TStringList* pPropertiesList,TStringList* pObsoletePropertyList) {
	m_OKButtonPressed = false;
	this->m_pEditApplicationPropertiesFrame->buildPropertiesEditor(pPropertiesList,pObsoletePropertyList);
	this->ShowModal();
	return m_OKButtonPressed;
}

/**
  * Copy our edited model to provided model
  */
void TEditPropertiesForm::copyTo(c_ApplicationPropertiesModel* pProperties) {
	this->m_pEditApplicationPropertiesFrame->getApplicationPropertiesModel()->copyTo(pProperties);
}

//---------------------------------------------------------------------------

void __fastcall TEditPropertiesForm::CancelButtonClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TEditPropertiesForm::OKButtonClick(TObject *Sender)
{
	this->m_OKButtonPressed = true;
	this->Close();
}
//---------------------------------------------------------------------------
#endif // __BCPLUSPLUS__

