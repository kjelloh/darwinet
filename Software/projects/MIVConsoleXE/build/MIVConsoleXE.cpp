/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------











































USEFORM("frames\DarwinetEngineFrameUnit.cpp", DarwinetEngineFrame); /* TFrame: File Type */
USEFORM("Forms\MIVFormUnit.cpp", MIVForm);
USEFORM("Forms\ApplicationFormUnit.cpp", ApplicationForm);
USEFORM("Forms\MainFormUnit.cpp", MainForm);
USEFORM("Forms\MessagingFormUnit.cpp", MessagingForm);
USEFORM("..\..\DarwinetRADLibXE\BusinessLogFormUnit.cpp", BusinessLogForm);
USEFORM("..\..\DarwinetRADLibXE\ABOUT.cpp", AboutBox);
USEFORM("..\..\DarwinetRADLibXE\EditPropertiesFormUnit.cpp", EditPropertiesForm);
USEFORM("..\..\DarwinetRADLibXE\EditPropertiesFrameUnit.cpp", EditApplicationPropertiesFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TBusinessLogForm), &BusinessLogForm);
		Application->CreateForm(__classid(TEditPropertiesForm), &EditPropertiesForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
