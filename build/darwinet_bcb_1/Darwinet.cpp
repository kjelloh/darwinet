//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------

























USEFORM("Forms\MainFormUnit.cpp", MainForm);
USEFORM("Forms\ApplicationFormUnit.cpp", ApplicationForm);
USEFORM("Forms\MIVFormUnit.cpp", MIVForm);
USEFORM("Forms\MessagingFormUnit.cpp", MessagingForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		SetApplicationMainFormOnTaskBar(Application, true);
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TApplicationForm), &ApplicationForm);
		Application->CreateForm(__classid(TMIVForm), &MIVForm);
		Application->CreateForm(__classid(TMessagingForm), &MessagingForm);
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
