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
	this->m_pEditApplicationPropertiesFrame->getTestBenchPropertiesModel()->copyTo(pProperties);
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

