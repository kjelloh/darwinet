// ---------------------------------------------------------------------------
// DARWINETSEPSIVALUEIMPL : Implementation of TDarwinetSEPSIValueImpl (CoClass: DarwinetSEPSIValue, Interface: IDarwinetSEPSIValue)
// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DarwinetSEPSIValueImpl.h"
#include "BusinessLogUnit.h"
// ---------------------------------------------------------------------------

/**
  * Proprietary destructor
  */
__fastcall  TDarwinetSEPSIValueImpl::~TDarwinetSEPSIValueImpl() {
	// Remove us as listener
	darwinet::c_DomainPath::shared_ptr pDomainPath;
	darwinet::c_ViewPath::shared_ptr pViewPath;
	darwinet::c_InstancePath::shared_ptr pInstancePath;
	darwinet::engine()->getDomain(pDomainPath)->getView(pViewPath)->getSEPSI()->getInstance(pInstancePath)->removeListener(this);
}

// Begin c_MIVValueInstanceListener

/**
  * Act on the change made to c_MIVValueInstance value
  */
void TDarwinetSEPSIValueImpl::actOnMIVValueInstanceValueChanged() {
	HRESULT result = this->FEvents->onValueChanged();
	if (!SUCCEEDED(result)) {
		// Failed
		c_LogString sMessage(__FUNCTION__" failed calling Event Sink. HRESULT = ");
		sMessage += c_DataRepresentationFramework::intToHexString(result);
		LOG_DESIGN_INSUFFICIENCY(sMessage);

	}
}

// End c_MIVValueInstanceListener

// ---------------------------------------------------------------------------
// TDarwinetSEPSIValueImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetSEPSIValueImpl::TDarwinetSEPSIValueImpl()
{
}


// ---------------------------------------------------------------------------
// TDarwinetSEPSIValueImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetSEPSIValueImpl::TDarwinetSEPSIValueImpl(const System::_di_IInterface Controller)
							  : inherited(Controller)
{
}


// ---------------------------------------------------------------------------
// TDarwinetSEPSIValueImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetSEPSIValueImpl::TDarwinetSEPSIValueImpl(Comobj::TComObjectFactory* Factory,
									  const System::_di_IInterface Controller)
							  : inherited(Factory, Controller)
{
	// Add us as listener
	darwinet::c_DomainPath::shared_ptr pDomainPath;
	darwinet::c_ViewPath::shared_ptr pViewPath;
	darwinet::c_InstancePath::shared_ptr pInstancePath;
	darwinet::engine()->getDomain(pDomainPath)->getView(pViewPath)->getSEPSI()->getInstance(pInstancePath)->addListener(this);
}

void __fastcall TDarwinetSEPSIValueImpl::EventSinkChanged(const System::_di_IInterface EventSink)
{
  FEvents.Bind(EventSink);
}

// ---------------------------------------------------------------------------
// TDarwinetSEPSIValueImpl - Class Factory
// ---------------------------------------------------------------------------
static void createFactory()
{
  new TCppAutoObjectFactory<TDarwinetSEPSIValueImpl>(Comserv::GetComServer(),
						   __classid(TDarwinetSEPSIValueImpl),
						   CLSID_DarwinetSEPSIValue,
						   Comobj::ciMultiInstance,
						   Comobj::tmApartment);
}
#pragma startup createFactory 32


STDMETHODIMP TDarwinetSEPSIValueImpl::setTo(BSTR sValue)
{
	LOG_METHOD_SCOPE;
	// OK. Lets create the MIV Delta (the actual change to us)
	// TODO: Implement the real mechanism (call to our in process view instance)
	//       For now, only call a method of the engine to get
	//       a MIVDelta to pass on.
	darwinet::c_DomainPath::shared_ptr pDomainPath;
	darwinet::c_ViewPath::shared_ptr pViewPath;
	darwinet::c_InstancePath::shared_ptr pInstancePath;
	darwinet::c_DarwinetString sDarwinetStringValue = c_DataRepresentationFramework::toUTF8String(_UTF16sz(sValue));
	darwinet::engine()->getDomain(pDomainPath)->getView(pViewPath)->getSEPSI()->getInstance(pInstancePath)->setValue(sDarwinetStringValue);
	return S_OK;
}
