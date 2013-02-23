/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
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
