/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef BusinessLogFormUnitH
#define BusinessLogFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TBusinessLogForm : public TForm
{
__published:	// IDE-managed Components
	TTimer *PollLogTimer;
	TPageControl *LogsPageControl;
	TTabSheet *AllTabSheet;
	TRichEdit *AllRichEdit;
	TTabSheet *BusinessTabSheet;
	TTabSheet *DesignInsuffiiciencyTabSheet;
	TTabSheet *DevelopmentTraceTabSheet;
	TRichEdit *BusinessLogRichEdit;
	TRichEdit *DesignInsufficiencyLogRichEdit;
	TRichEdit *DeveloperLogRichEdit;
	void __fastcall PollLogTimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TBusinessLogForm(TComponent* Owner);

	/**
	  * Destructor
	  */
	__fastcall ~TBusinessLogForm();

	/**
	  * returns this instance of the form,
	  * creating it is if does not yet exist.
	  */
	static TBusinessLogForm* instance();

	/**
	  * Docks this form to provided panel
	  */
	void DockToPanel(TPanel* panel);

// 120306/KoH. Not used
//	/**
//	  * Start this Log view
//	  */
//	void start();

// 120306/KoH. Not used
//	/**
//	  * Stop this Log View
//	  */
//	void stop();

};
//---------------------------------------------------------------------------
extern PACKAGE TBusinessLogForm *BusinessLogForm;
//---------------------------------------------------------------------------
#endif
