//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <ComServ.hpp>
#include <tchar.h>
//---------------------------------------------------------------------------
#include "DarwinetEngineImpl.h"
#include "DarwinetDomainImpl.h"
#include "DarwinetDomainViewImpl.h"
#include "DarwinetSEPSIImpl.h"
#include "DarwinetSEPSIValueImpl.h"




























USEFORM("MainFormUnit.cpp", MainForm);
USEFORM("frames\PeerMailFrameUnit.cpp", PeerMailFrame); /* TFrame: File Type */
USEFORM("frames\IMAPClientFrameUnit.cpp", IMAPClientFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
#pragma link "ComServ.obj"
/**
  * notes on Using RAD Studio to build and use COM servers
  * http://docwiki.embarcadero.com/RADStudio/XE4/en/Class_Hierarchy_in_an_ActiveX_Control_(DAX)
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

/**
  * When a darwinet Application uses COM to connect to the Darwinet Engine the design
  * looks like this.
  *
  * Darwinet Application <-> Darwinet Server COM Proxy <-> ... COM ... <-> Darwinet Client Proxy <-> Darwinet Engine
  *
  * The general design pattern is:
  *
  * Darwinet Application <-> Darwinet Engine Proxy <-> Protocol <-> Darwinet Client PRoxy <-> Darwinet Engine
  *
  * Should the client use an in process Darwinet Engine this redices to
  * Darwinet Application <-> Darwinet Engine
  *
  * Signalling is asynchronous by default menaing the application calls the server without requesting a result in return
  * Instead the Server calls the Application at some later time when a result is available.
  *
  * When using COM as connection protocol in RAD Studio one of the folowing layering may be used.
  *
  * <-> Darwinet TLB Server Proxy <-> TLB Object <-> ...COM... <-> TLB Object <-> Darwinet TLB Client Proxy <->
  *
  *
  *
  *
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
