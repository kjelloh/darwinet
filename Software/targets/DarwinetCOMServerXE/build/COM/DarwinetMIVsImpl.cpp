// ---------------------------------------------------------------------------
// DARWINETMIVIMPL : Implementation of TDarwinetMIVsImpl (CoClass: DarwinetMIVs, Interface: IDarwinetMIVs)
// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DarwinetMIVsImpl.h"
#include "BusinessLogUnit.h"

// ---------------------------------------------------------------------------
// TDarwinetMIVsImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetMIVsImpl::TDarwinetMIVsImpl()
{
	LOG_METHOD_SCOPE;
}


// ---------------------------------------------------------------------------
// TDarwinetMIVsImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetMIVsImpl::TDarwinetMIVsImpl(const System::_di_IInterface Controller)
							  : inherited(Controller)
{
	LOG_METHOD_SCOPE_S(_UTF8sz("const System::_di_IInterface Controller"));
}


// ---------------------------------------------------------------------------
// TDarwinetMIVsImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetMIVsImpl::TDarwinetMIVsImpl(Comobj::TComObjectFactory* Factory,
									  const System::_di_IInterface Controller)
							  : inherited(Factory, Controller)
{
	LOG_METHOD_SCOPE_S(_UTF8sz("Comobj::TComObjectFactory* Factory,const System::_di_IInterface Controller"));
	// Bind us to the Engine
	this->m_pMIVs = darwinet::engine()->getClientProxyInterface()->getMIVs(Controller,this);
}

void __fastcall TDarwinetMIVsImpl::EventSinkChanged(const System::_di_IInterface EventSink)
{
	LOG_METHOD_SCOPE;
  FEvents.Bind(EventSink);
}

// ---------------------------------------------------------------------------
// TDarwinetMIVsImpl - Class Factory
// ---------------------------------------------------------------------------
static void createFactory()
{
  new TCppAutoObjectFactory<TDarwinetMIVsImpl>(Comserv::GetComServer(),
						   __classid(TDarwinetMIVsImpl),
						   CLSID_DarwinetMIVs,
						   Comobj::ciMultiInstance,
						   Comobj::tmApartment);
}
#pragma startup createFactory 32


STDMETHODIMP TDarwinetMIVsImpl::setValue(BSTR sInstancePath, BSTR sValue)
{
	// Set the value with provided path to provided value
	LOG_METHOD_SCOPE;
	String sInstancePathString(sInstancePath);
	String sValueString(sValue);
	LOG_NOT_IMPLEMENTED;

	if (this->m_pMIVs) {
		darwinet::c_DarwinetString sDarwinetInstancePath = c_DataRepresentationFramework::toUTF8String(_UTF16sz(sInstancePathString.c_str()));
		darwinet::c_DarwinetString sDarwinetValue = c_DataRepresentationFramework::toUTF8String(_UTF16sz(sValueString.c_str()));
		this->m_pMIVs->setValue(sDarwinetInstancePath,sDarwinetValue);
	}

	return S_OK;
}

