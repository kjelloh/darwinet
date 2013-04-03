/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef MIVFormUnitH
#define MIVFormUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TMIVForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TMIVForm(TComponent* Owner);

	/**
	  * Returns the singleton instance of this form.
	  * Creating it if it does not yet exist.
	  */
	static TMIVForm* instance();

};
//---------------------------------------------------------------------------
extern PACKAGE TMIVForm *MIVForm;
//---------------------------------------------------------------------------
#endif
