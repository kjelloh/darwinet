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


















USEFORM("Forms\MessagingFormUnit.cpp", MessagingForm);
USEFORM("Forms\MIVFormUnit.cpp", MIVForm);
USEFORM("Forms\ApplicationFormUnit.cpp", ApplicationForm);
USEFORM("Forms\MainFormUnit.cpp", MainForm);
USEFORM("..\..\..\common\cpp\DarwinetRADLib\BusinessLogFormUnit.cpp", BusinessLogForm);
USEFORM("..\..\..\common\cpp\DarwinetRADLib\ABOUT.cpp", AboutBox);
USEFORM("..\..\..\common\cpp\DarwinetRADLib\EditPropertiesFormUnit.cpp", EditPropertiesForm);
USEFORM("..\..\..\common\cpp\DarwinetRADLib\EditPropertiesFrameUnit.cpp", EditApplicationPropertiesFrame); /* TFrame: File Type */
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
