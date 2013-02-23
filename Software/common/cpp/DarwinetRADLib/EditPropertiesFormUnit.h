/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef EditPropertiesFormUnitH
#define EditPropertiesFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Dialogs.hpp>
#include "EditPropertiesFrameUnit.h"
#include <boost/shared_ptr.hpp>

//---------------------------------------------------------------------------
class TEditPropertiesForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *BottomPanel;
	TButton *OKButton;
	TButton *CancelButton;
	TOpenDialog *OpenDialog1;
	TPanel *Panel1;
//	void __fastcall ValueListEditor1EditButtonClick(TObject *Sender);
//	void __fastcall ValueListEditor1GetPickList(TObject *Sender,
//          const AnsiString KeyName, TStrings *Values);
	void __fastcall CancelButtonClick(TObject *Sender);
	void __fastcall OKButtonClick(TObject *Sender);
private:	// User declarations

	/**
	  * Private storage of wether OK button was pressed to close dialog.
	  * Value returned by Execute method.
	  */
	bool m_OKButtonPressed;

	/**
	  * Private storage of the property editor frame used by this dialog
	  */
	TEditApplicationPropertiesFrame* m_pEditApplicationPropertiesFrame;

public:		// User declarations

// Removed 111205/KoH
//	/**
//	  * returns this singleton, creating it if it does not yet exist
//	  */
//	static TEditPropertiesForm* instance();

	__fastcall TEditPropertiesForm(TComponent* Owner,TEditApplicationPropertiesFrame* pEditApplicationPropertiesFrame);

	/**
	  * Executes this dialog with provided StringList
	  */
	bool Execute(TStringList* pPropertiesList,TStringList* pObsoletePropertyList);

	/**
	  * Copy our edited model to provided model
	  */
	void copyTo(c_ApplicationPropertiesModel* pProperties);

};
//---------------------------------------------------------------------------
extern PACKAGE TEditPropertiesForm *EditPropertiesForm;
//---------------------------------------------------------------------------
#endif
