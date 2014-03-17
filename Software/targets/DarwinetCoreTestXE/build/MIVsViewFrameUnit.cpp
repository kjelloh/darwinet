//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MIVsViewFrameUnit.h"
#include "SEPSISeed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMIVsViewFrame *MIVsViewFrame;
//---------------------------------------------------------------------------
typedef std::map<TMIVsViewFrame*,c_TestBenchClientSideProxy::shared_ptr> c_TestBenchClientSideProxyMap;
c_TestBenchClientSideProxyMap TestBenchClientSideProxyMap;

c_TestBenchClientSideProxy::shared_ptr getTestBenchClientSideProxy(TMIVsViewFrame* pMIVsViewFrame) {
	c_TestBenchClientSideProxy::shared_ptr result = TestBenchClientSideProxyMap[pMIVsViewFrame];
	if (!result) {
		result.reset(new c_TestBenchClientSideProxy());
		TestBenchClientSideProxyMap[pMIVsViewFrame] = result;
	}
	return result;
}

unsigned int TMIVsViewFrame::m_instanceCount = 0;
//---------------------------------------------------------------------------

void __fastcall TMIVsViewFrame::CMOnMIVsChange(TWMNoParams Message) {
	ShowMessage("TMIVsViewFrame::CMOnMIVsChange :)");
}
//---------------------------------------------------------------------------
__fastcall TMIVsViewFrame::TMIVsViewFrame(TComponent* Owner,unsigned int index)
	: TFrame(Owner)
	  ,m_index(index)
{
	++m_instanceCount;
	this->Name = String("MIVsViewFrame") + String(m_instanceCount);
}

//---------------------------------------------------------------------------
void __fastcall TMIVsViewFrame::MyIntSpinEditChange(TObject *Sender)
{
	// Update our Viewed MIVs with the new value
	LOG_DESIGN_INSUFFICIENCY(c_LogString("TMIVsViewFrame::MyIntSpinEditChange sets Proxy callback windows handle at each call."));
	// TODO: Find a better way to report our windows handle to the GUI Client Proxy.
	//       Note: We canät do it in the constructor as we have not yet been assigned our final windos hanlder there!
	getTestBenchClientSideProxy(this)->getGUIClientproxy(m_index)->setGUIWindowhandle(this->WindowHandle);
	getTestBenchClientSideProxy(this)->getGUIClientproxy(m_index)->setMIVsValue("myInt",AnsiString(this->MyIntSpinEdit->Value).c_str());
}
//---------------------------------------------------------------------------
