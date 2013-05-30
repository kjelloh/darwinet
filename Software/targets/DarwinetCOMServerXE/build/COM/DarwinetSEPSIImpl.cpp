// ---------------------------------------------------------------------------
// DARWINETMIVIMPL : Implementation of TDarwinetSEPSIImpl (CoClass: DarwinetSEPSI, Interface: IDarwinetSEPSI)
// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DarwinetSEPSIImpl.h"
#include "BusinessLogUnit.h"

// ---------------------------------------------------------------------------
// TDarwinetSEPSIImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetSEPSIImpl::TDarwinetSEPSIImpl()
{
	LOG_METHOD_SCOPE;
}


// ---------------------------------------------------------------------------
// TDarwinetSEPSIImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetSEPSIImpl::TDarwinetSEPSIImpl(const System::_di_IInterface Controller)
							  : inherited(Controller)
{
	LOG_METHOD_SCOPE_S(_UTF8sz("const System::_di_IInterface Controller"));
}


// ---------------------------------------------------------------------------
// TDarwinetSEPSIImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetSEPSIImpl::TDarwinetSEPSIImpl(Comobj::TComObjectFactory* Factory,
									  const System::_di_IInterface Controller)
							  : inherited(Factory, Controller)
{
	LOG_METHOD_SCOPE_S(_UTF8sz("Comobj::TComObjectFactory* Factory,const System::_di_IInterface Controller"));
	// Bind us to the Engine
	this->m_pDarwinetEngineSEPSI = darwinet::engine()->getClientProxyInterface()->getSEPSI(Controller,this);
}

void __fastcall TDarwinetSEPSIImpl::EventSinkChanged(const System::_di_IInterface EventSink)
{
	LOG_METHOD_SCOPE;
  FEvents.Bind(EventSink);
}

// ---------------------------------------------------------------------------
// TDarwinetSEPSIImpl - Class Factory
// ---------------------------------------------------------------------------
static void createFactory()
{
  new TCppAutoObjectFactory<TDarwinetSEPSIImpl>(Comserv::GetComServer(),
						   __classid(TDarwinetSEPSIImpl),
						   CLSID_DarwinetSEPSI,
						   Comobj::ciMultiInstance,
						   Comobj::tmApartment);
}
#pragma startup createFactory 32

STDMETHODIMP TDarwinetSEPSIImpl::getValue(BSTR sInstancePath, DarwinetSEPSIValue** pValue)

{
//	LOG_METHOD_SCOPE;
//	if (!m_COMIDarwinetSEPSIValue) {
//		c_LogString sMessage(__FUNCTION__" Called CoDarwinetSEPSIValue::Create() to create m_COMIDarwinetSEPSIValue");
//		LOG_DEVELOPMENT_TRACE(sMessage);
//		m_COMIDarwinetSEPSIValue = CoDarwinetSEPSIValue::Create();
//	}
//	return m_COMIDarwinetSEPSIValue;
	LOG_METHOD_SCOPE;
	if (!m_COMIDarwinetSEPSIValue) {
		c_LogString sMessage(__FUNCTION__" Called CoDarwinetSEPSIValue::Create() to create m_COMIDarwinetSEPSIValue");
		LOG_DEVELOPMENT_TRACE(sMessage);
		m_COMIDarwinetSEPSIValue = CoDarwinetSEPSIValue::Create();
	}
	*pValue = m_COMIDarwinetSEPSIValue;
	return S_OK;
}

/**
* Destructor added to track destruction of this instance
*/
__fastcall TDarwinetSEPSIImpl::~TDarwinetSEPSIImpl() {
	LOG_METHOD_SCOPE;
}

