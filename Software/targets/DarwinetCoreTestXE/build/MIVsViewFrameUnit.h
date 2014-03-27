//---------------------------------------------------------------------------

#ifndef MIVsViewFrameUnitH
#define MIVsViewFrameUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <boost/shared_ptr.hpp>
#include "DarwinetWindowsGUIInterface.h"
//---------------------------------------------------------------------------
class TMIVsViewFrame : public TFrame
{
__published:	// IDE-managed Components
	TSpinEdit *MyIntSpinEdit;
	void __fastcall MyIntSpinEditChange(TObject *Sender);
private:	// User declarations
	static unsigned int m_instanceCount;
	unsigned int m_index;

//	void __fastcall CMOnMIVsChange(TWMNoParams Message);
	void __fastcall CMOnMIVsChange(TMessage Message);
	BEGIN_MESSAGE_MAP
//	   MESSAGE_HANDLER(WM_USER+1, TWMNoParams, CMOnMIVsChange)
//	   MESSAGE_HANDLER(WM_USER+1, TMessage, CMOnMIVsChange)
	   MESSAGE_HANDLER(darwinet_seed::eWINDOWS_MESSAGE_ID_OnDarwinetSignal, TMessage, CMOnMIVsChange)

	END_MESSAGE_MAP(TFrame)
	// Note that END_MESSAGE_MAP needs parameter to B a s e class TFrame (not to us TMIVsViewFrame). See http://stackoverflow.com/questions/10059559/stack-overflow-when-trying-to-set-up-user-defined-message-handler

public:		// User declarations

	void updateGUIToReflectChanges();

	void open();

	__fastcall TMIVsViewFrame(TComponent* Owner,unsigned int index);
};
//---------------------------------------------------------------------------
extern PACKAGE TMIVsViewFrame *MIVsViewFrame;
//---------------------------------------------------------------------------
#endif
