//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Graphics.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//----------------------------------------------------------------------------

class PACKAGE TAboutBox : public TForm
{
__published:
	TPanel *Panel1;
	TImage *ProgramIcon;
	TLabel *ProductName;
	TLabel *Version;
	TLabel *Copyright;
	TLabel *Comments;
	TPanel *Panel2;
	TButton *OKButton;
	TMemo *HistoryViewMemo;
private:
public:
	virtual __fastcall TAboutBox(TComponent* AOwner);
	/**
	  * returns this insatnce of the About dialog form,
	  * creating it is it does not yet exist.
	  */
	static TAboutBox* instance();

	/**
	  * Executes this about dialog.
	  * Will always return true.
	  */
	bool Execute();

//	/**
//	  * returns the Date and time when this application was built
//	  */
//	String getDateAndTimeOfBuildString();

};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif
