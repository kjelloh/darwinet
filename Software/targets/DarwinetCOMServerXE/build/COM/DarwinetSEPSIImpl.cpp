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
	this->m_pSEPSI = darwinet::engine()->getClientProxyInterface()->getSEPSI(Controller,this);
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


STDMETHODIMP TDarwinetSEPSIImpl::setValue(BSTR sInstancePath, BSTR sValue)
{
	// Set the value with provided path to provided value
	LOG_METHOD_SCOPE;
	String sInstancePathString(sInstancePath);
	String sValueString(sValue);
	LOG_NOT_IMPLEMENTED;

	if (this->m_pSEPSI) {
		darwinet::c_DarwinetString sDarwinetInstancePath = c_DataRepresentationFramework::toUTF8String(_UTF16sz(sInstancePathString.c_str()));
		darwinet::c_DarwinetString sDarwinetValue = c_DataRepresentationFramework::toUTF8String(_UTF16sz(sValueString.c_str()));
		this->m_pSEPSI->setValue(sDarwinetInstancePath,sDarwinetValue);
	}

	return S_OK;
}

