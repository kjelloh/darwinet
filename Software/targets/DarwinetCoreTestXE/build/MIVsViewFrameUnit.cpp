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
typedef std::map<TMIVsViewFrame*,darwinet_seed::c_TestBenchClientSideProxy::shared_ptr> c_TestBenchClientSideProxyMap;
c_TestBenchClientSideProxyMap TestBenchClientSideProxyMap;

darwinet_seed::c_TestBenchClientSideProxy::shared_ptr getTestBenchClientSideProxy(TMIVsViewFrame* pMIVsViewFrame) {
	darwinet_seed::c_TestBenchClientSideProxy::shared_ptr result = TestBenchClientSideProxyMap[pMIVsViewFrame];
	if (!result) {
		result.reset(new darwinet_seed::c_TestBenchClientSideProxy());
		TestBenchClientSideProxyMap[pMIVsViewFrame] = result;
	}
	return result;
}

unsigned int TMIVsViewFrame::m_instanceCount = 0;
//---------------------------------------------------------------------------
/**
  * We need to inhibit the OnChange event handler action of GUI components
  * when we update GUI values on events sent from darwinet data model.
  * We do this
  * 1. Map a booelan inhibit flag to each component to inhibit.
  * 2. Set the flag on internal component value set
  * 3. Check the flag in the OnChange event handler
  *
  * Further, we use constructor/destructor flag set/reset to secure flag
  * handling in case of exceptions (See c_ScopedGUIOnChangeInhibiter).
  */
typedef std::map<TComponent*,bool> c_InhibitGUIOnchangeHandler;
c_InhibitGUIOnchangeHandler InhibitGUIOnchangeHandler;

class c_ScopedGUIOnChangeInhibiter {
public:
	c_ScopedGUIOnChangeInhibiter(TComponent* pComponent)
		: m_pComponent(pComponent)
	{
		InhibitGUIOnchangeHandler[m_pComponent] = true; // Set inhibit flag
	}

	~c_ScopedGUIOnChangeInhibiter() {
		InhibitGUIOnchangeHandler[m_pComponent] = false; // reset inhibit flag
	}
private:

	TComponent* m_pComponent;
};

#define SCOPED_ONCHANGE_INHIBIT(X) c_ScopedGUIOnChangeInhibiter ScopedGUIOnChangeInhibiter(X)

//void __fastcall TMIVsViewFrame::CMOnMIVsChange(TWMNoParams Message) {
void __fastcall TMIVsViewFrame::CMOnMIVsChange(TMessage Message) {
	try {
		if (Message.LParam != NULL) {
			darwinet_seed::c_GUIClientproxy::c_SignalString sSignal(reinterpret_cast<char*>(Message.LParam));
			String sMessage = "TMIVsViewFrame::CMOnMIVsChange. Received sSignal=\"";
			sMessage += sSignal.c_str();
			sMessage += "\n";
			ShowMessage(sMessage);

			darwinet_seed::c_Signal signal(darwinet_seed::createSignalFromString(sSignal));
			darwinet_seed::c_GUIClientproxy::c_SignalString sEventId = signal.getValue(darwinet_seed::SIGNAL_FIELD_MAPPER[darwinet_seed::eSignalField_MIVsEventId]);
			if (sEventId == _UTF8sz("OnMIVValue")) {
				darwinet_seed::c_GUIClientproxy::c_SignalString sMIV_Element = signal.getValue(darwinet_seed::SIGNAL_FIELD_MAPPER[darwinet_seed::eSignalField_MIVsEventSourceId]);
				if (sMIV_Element == _UTF8sz("myInt")) {
					String sValue(signal.getValue(darwinet_seed::SIGNAL_FIELD_MAPPER[darwinet_seed::eSignalField_MIVsEventValue]).c_str());
	//				InhibitGUIOnchangeHandler[this->MyIntSpinEdit] = true;
					SCOPED_ONCHANGE_INHIBIT(this->MyIntSpinEdit);
					this->MyIntSpinEdit->Value = sValue.ToInt();
	//				InhibitGUIOnchangeHandler[this->MyIntSpinEdit] = false;
				}
				else {
					// Not myInt
				}
			}
			else {
				// Unhandled signal
				c_LogString sMessage(__FUNCTION__);
				sMessage += _UTF8sz(" unhandled event ");
				sMessage += sEventId;
				LOG_DESIGN_INSUFFICIENCY(sMessage);

            }
		}
		else {
			ShowMessage("TMIVsViewFrame::CMOnMIVsChange received NULL signal");
		}
	}
	CATCH_AND_LOG_IDE_STD_AND_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY;
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
	if (!InhibitGUIOnchangeHandler[this->MyIntSpinEdit]) {
		// Update our Viewed MIVs with the new value
		LOG_DESIGN_INSUFFICIENCY(c_LogString("TMIVsViewFrame::MyIntSpinEditChange sets Proxy callback windows handle at each call."));
		// TODO: Find a better way to report our windows handle to the GUI Client Proxy.
		//       Note: We canät do it in the constructor as we have not yet been assigned our final windos hanlder there!
		getTestBenchClientSideProxy(this)->getGUIClientproxy(m_index)->setGUIWindowhandle(this->WindowHandle);
		getTestBenchClientSideProxy(this)->getGUIClientproxy(m_index)->setMIVsValue(_UTF8sz("myInt"),_UTF8sz(AnsiString(this->MyIntSpinEdit->Value).c_str()));
	}
}
//---------------------------------------------------------------------------
