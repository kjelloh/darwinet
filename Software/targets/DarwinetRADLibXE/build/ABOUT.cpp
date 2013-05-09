//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
#include "BusinessLogUnit.h" // DESIGN_INSUFFICIENCY_LOG(...)
#include "ApplicationEnvironment.h"
//---------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutBox *AboutBox = NULL;

//---------------------------------------------------------------------
/**
  * returns this insatnce of the About dialog form,
  * creating it is it does not yet exist.
  */
TAboutBox* TAboutBox::instance() {
	if (AboutBox==NULL) {
// 120306/KoH, Do not use Application->CreateForm in own code. See https://forums.embarcadero.com/messageview.jspa?messageID=440601&stqc=true
//		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		AboutBox = new TAboutBox(Application->MainForm);
	}
	return AboutBox;
}
//---------------------------------------------------------------------
/**
  * Executes this about dialog.
  * Will always return true.
  */
bool TAboutBox::Execute() {
	this->ShowModal();
	return true;
}
//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
	ProgramIcon->Picture->Icon = Application->Icon;

	this->ProductName->Caption = c_Application::getVersionInfoProductName().c_str();
	this->Version->Caption = c_Application::getVersionInfoVersion().c_str();
	this->Copyright->Caption = String("Copyright: ") + c_Application::getVersionInfoCopyRight().c_str();
	this->Comments->Caption = c_Application::getVersionInfoComments().c_str();

	c_FilePath HistoryOfChangesFilePath = c_ApplicationRunTimeEnvironent::instance()->getRootPath();
	HistoryOfChangesFilePath += u"HistoryOfChanges.txt";

	if (this->HistoryViewMemo->Lines->Count < 5) {
		// Interpret as empty (allow for dummy lines in IDE editor)
		try {
			this->HistoryViewMemo->Lines->LoadFromFile(HistoryOfChangesFilePath.toString().c_str());
		} catch (...) {
			// Failed to load the file
		}
	}

	if (this->HistoryViewMemo->Lines->Count < 5) {
		// Interpret as No file found
		this->HistoryViewMemo->Font->Size = 18;
		this->HistoryViewMemo->Lines->Add(AnsiString(HistoryOfChangesFilePath.toString().c_str()) + " not found. Please reinstall this product to fix this and other problems.");
	}
}
//---------------------------------------------------------------------

///**
//  * returns the Date and time when this application was built
//  */
//String TAboutBox::getDateAndTimeOfBuildString() {
//	VersionInfo anInfo(c_Application::ExeName());
//	String sVersion = "Version: ";
//	if (anInfo.hasInfo()) {
//		sVersion += anInfo.majorVersion();
//		sVersion += ".";
//		sVersion += anInfo.minorVersion();
//		sVersion += ".";
//		sVersion += anInfo.build();
//		sVersion += ".";
//		sVersion += anInfo.subBuild();
//	}
//	else {
//		LOG_DESIGN_INSUFFICIENCY(_Literalsz("TAboutBox::getDateAndTimeOfBuildString, failed to retreive version information"));
//		sVersion += "??";
//	}
//
//	static String BUILD_DATE_AND_TIME_STRING = sVersion + " Build:" __DATE__ "  " __TIME__;
//
//	return BUILD_DATE_AND_TIME_STRING;
//}

