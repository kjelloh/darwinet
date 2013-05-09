/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef ApplicationFormUnitH
#define ApplicationFormUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Samples.Spin.hpp>
#include "DarwinetFramework.h"


//---------------------------------------------------------------------------
class TApplicationForm : public TForm
{
__published:	// IDE-managed Components
	TSpinEdit *SpinEdit1;
private:	// User declarations

	/**
	  * Private storage of our Domain
	  */
	darwinet::c_DarwinetDomain::shared_ptr m_pDomain;

	/**
	  * Private storage of our View
	  */
	darwinet::c_DomainView::shared_ptr m_pView;

	/**
	  * Private storage of our MIV
	  */
	darwinet::c_MIV::shared_ptr m_pMIV;

	/**
	  * Private storage of Current mirrored Spin Value
	  */
	int m_MirroredSpinValue;

public:		// User declarations
	__fastcall TApplicationForm(TComponent* Owner);

	/**
	  * Returns the singleton instance of this form.
	  * Creating it if it does not yet exist.
	  */
	static TApplicationForm* instance();
};
//---------------------------------------------------------------------------
extern PACKAGE TApplicationForm *ApplicationForm;
//---------------------------------------------------------------------------
#endif
