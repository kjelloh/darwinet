//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <ComServ.hpp>
#include <tchar.h>
//---------------------------------------------------------------------------
#include "DarwinetEngineImpl.h"
#include "DarwinetDomainImpl.h"

#include "DarwinetDomainViewImpl.h"



USEFORM("MainFormUnit.cpp", MainForm);
//---------------------------------------------------------------------------
#pragma link "ComServ.obj"
/**
  * notes on Using RAD Studio to build and use COM servers
  *
  * Import COM Object and COM Components wrappers to a client using <Component>/<Import Component>
  *		* Select <Import a type library>
  * 	* Search for "Darwinet"
  *		* Select the type library
  * 	  (note. If you have experimented with COM servers there may be
  *		   "left-overs" of registered Type Libraries that are no longer existing or active.
  *        You may then have to delete them manually using regedit started from Command Prompt.)
  *     * Set <Unit Path> to a sub-folder of your client application "\ImportedTLB\".
  *       This enables you to know what you have imported and where it is.
  *     * Check the <Generate Component Wrappers>
  *     * In the next Dialog, select <Add unit to _your_project_>. In this way
  *       the wrappres generated will be compiled as part of your project.
  */
static Comserv::TCppActiveXModule _ax_module(true);

WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainForm), &MainForm);
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
