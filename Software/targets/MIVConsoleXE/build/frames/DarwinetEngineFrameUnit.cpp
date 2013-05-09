//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DarwinetEngineFrameUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DarwinetCOMServer_OCX"
#pragma resource "*.dfm"
TDarwinetEngineFrame *DarwinetEngineFrame;
//---------------------------------------------------------------------------
__fastcall TDarwinetEngineFrame::TDarwinetEngineFrame(TComponent* Owner)
	: TFrame(Owner)
{
//	this->DarwinetEngine1->Connect();
}
//---------------------------------------------------------------------------
