//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MIVsViewFrameUnit.h"
#include "SEPSISeed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
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

//---------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
#define SCOPED_ONCHANGE_INHIBIT(X) c_ScopedGUIOnChangeInhibiter ScopedGUIOnChangeInhibiter(X)
//---------------------------------------------------------------------------
void __fastcall TMIVsViewFrame::CMOnMIVsChange(TMessage Message) {
	LOG_METHOD_SCOPE;
	try {
		if (Message.LParam != NULL) {
			darwinet_seed::c_GUIClientproxy::c_SignalString sSignal(reinterpret_cast<char*>(Message.LParam));
			String sMessage = "TMIVsViewFrame::CMOnMIVsChange. Received sSignal=\"";
			sMessage += sSignal.c_str();
			LOG_BUSINESS(toLogString(sMessage));
//			ShowMessage(sMessage);

			darwinet_seed::c_Signal signal(darwinet_seed::createSignalFromString(sSignal));
			LOG_BUSINESS(c_LogString("Parsed Signal = ") + darwinet_seed::log::toLogString(signal));
			darwinet_seed::c_GUIClientproxy::c_SignalString sReceiver = signal.getValue(darwinet_seed::SIGNAL_FIELD_MAPPER[darwinet_seed::eSignalField_SignalReceiver]);
			darwinet_seed::c_GUIClientproxy::c_SignalString sEventId = signal.getValue(darwinet_seed::SIGNAL_FIELD_MAPPER[darwinet_seed::eSignalField_MIVsEventId]);
//			darwinet_seed::c_GUIClientproxy::c_SignalString sEventId = signal.getValue(darwinet_seed::c_CaptionNode(" Body.MIVsEvent.Id"));
			if (sEventId == darwinet_seed::MIVS_EVENT_MAPPER[darwinet_seed::eMIVsEventId_OnMIVValueChanged]) {
				darwinet_seed::c_GUIClientproxy::c_SignalString sMIV_Element = signal.getValue(darwinet_seed::SIGNAL_FIELD_MAPPER[darwinet_seed::eSignalField_MIVsEventSourceId]);
				if (sMIV_Element == _UTF8sz("myInt:0")) {
					String sValue(signal.getValue(darwinet_seed::SIGNAL_FIELD_MAPPER[darwinet_seed::eSignalField_MIVsEventValue]).c_str());
					SCOPED_ONCHANGE_INHIBIT(this->MyIntSpinEdit);
					this->MyIntSpinEdit->Value = sValue.ToInt();
				}
				else if (sMIV_Element == _UTF8sz("myString:0")) {
					String sValue(signal.getValue(darwinet_seed::SIGNAL_FIELD_MAPPER[darwinet_seed::eSignalField_MIVsEventValue]).c_str());
					SCOPED_ONCHANGE_INHIBIT(this->MyTextEdit);
					this->MyTextEdit->Text = sValue;
				}
				else {
					LOG_BUSINESS(c_LogString(METHOD_NAME + ", Received unknwon MIV Id = ") + sMIV_Element);
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
	this->updateGUIToReflectChanges();
}

//---------------------------------------------------------------------------
void TMIVsViewFrame::updateGUIToReflectChanges() {
	this->MyIntSpinEdit->Enabled = getTestBenchClientSideProxy(this)->getGUIClientproxy(m_index)->isOpen();
}


//---------------------------------------------------------------------------
void TMIVsViewFrame::open() {
	getTestBenchClientSideProxy(this)->getGUIClientproxy(m_index)->setGUIWindowhandle(this->WindowHandle);
	getTestBenchClientSideProxy(this)->getGUIClientproxy(m_index)->open();
}

//---------------------------------------------------------------------------
__fastcall TMIVsViewFrame::TMIVsViewFrame(TComponent* Owner,unsigned int index)
	: TFrame(Owner)
	  ,m_index(index)
{
	++m_instanceCount;
	this->Name = String("MIVsViewFrame") + String(m_instanceCount);
	this->updateGUIToReflectChanges();
}

//---------------------------------------------------------------------------
void __fastcall TMIVsViewFrame::MyIntSpinEditChange(TObject *Sender)
{
	if (!InhibitGUIOnchangeHandler[this->MyIntSpinEdit]) {
		// Update our Viewed MIVs with the new value
		LOG_DESIGN_INSUFFICIENCY(c_LogString("TMIVsViewFrame::MyIntSpinEditChange sets Proxy callback windows handle at each call."));
		// TODO: Find a better way to report our windows handle to the GUI Client Proxy.
		//       Note: We can't do it in the constructor as we have not yet been assigned our final windows handler there!
		getTestBenchClientSideProxy(this)->getGUIClientproxy(m_index)->setGUIWindowhandle(this->WindowHandle);
		getTestBenchClientSideProxy(this)->getGUIClientproxy(m_index)->setMIVsValue(_UTF8sz("myInt:0"),_UTF8sz(AnsiString(this->MyIntSpinEdit->Value).c_str()));
	}
}
//---------------------------------------------------------------------------

void __fastcall TMIVsViewFrame::MyTextEditChange(TObject *Sender)
{
	if (!InhibitGUIOnchangeHandler[this->MyTextEdit]) {
		// The change is made by the user
		// Update our Viewed MIVs with the new value
		LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString("Sets Proxy callback windows handle at each call."));
		// TODO: Find a better way to report our windows handle to the GUI Client Proxy.
		//       Note: We can't do it in the constructor as we have not yet been assigned our final windows handler there!
		getTestBenchClientSideProxy(this)->getGUIClientproxy(m_index)->setGUIWindowhandle(this->WindowHandle);
		getTestBenchClientSideProxy(this)->getGUIClientproxy(m_index)->setMIVsValue(_UTF8sz("myString:0"),_UTF8sz(AnsiString(this->MyTextEdit->Text).c_str()));
    }
}
//---------------------------------------------------------------------------


