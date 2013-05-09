//---------------------------------------------------------------------------

#ifndef DarwinetEngineFrameUnitH
#define DarwinetEngineFrameUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "DarwinetCOMServer_OCX.h"
#include <Vcl.OleServer.hpp>
//---------------------------------------------------------------------------
class TDarwinetEngineFrame : public TFrame
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TDarwinetEngineFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDarwinetEngineFrame *DarwinetEngineFrame;
//---------------------------------------------------------------------------
#endif
