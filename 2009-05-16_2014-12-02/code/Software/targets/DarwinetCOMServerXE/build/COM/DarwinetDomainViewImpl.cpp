// ---------------------------------------------------------------------------
// DARWINETDOMAINVIEWIMPL : Implementation of TDarwinetDomainViewImpl (CoClass: DarwinetDomainView, Interface: IDarwinetDomainView)
// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DarwinetDomainViewImpl.h"
#include "BusinessLogUnit.h"


// ---------------------------------------------------------------------------
// TDarwinetDomainViewImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainViewImpl::TDarwinetDomainViewImpl()
{
	LOG_METHOD_SCOPE_S(_UTF8sz("()"));
}


// ---------------------------------------------------------------------------
// TDarwinetDomainViewImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainViewImpl::TDarwinetDomainViewImpl(const System::_di_IInterface Controller)
							  : inherited(Controller)
{
	LOG_METHOD_SCOPE_S(_UTF8sz("(const System::_di_IInterface Controller)"));
}


// ---------------------------------------------------------------------------
// TDarwinetDomainViewImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainViewImpl::TDarwinetDomainViewImpl(Comobj::TComObjectFactory* Factory,
									  const System::_di_IInterface Controller)
							  : inherited(Factory, Controller)
{
	LOG_METHOD_SCOPE_S(_UTF8sz("(Comobj::TComObjectFactory* Factory,const System::_di_IInterface Controller)"));
}

void __fastcall TDarwinetDomainViewImpl::EventSinkChanged(const System::_di_IInterface EventSink)
{
  LOG_METHOD_SCOPE;
  FEvents.Bind(EventSink);
}

// ---------------------------------------------------------------------------
// TDarwinetDomainViewImpl - Class Factory
// ---------------------------------------------------------------------------
static void createFactory()
{
	LOG_FUNCTION_SCOPE;
  new TCppAutoObjectFactory<TDarwinetDomainViewImpl>(Comserv::GetComServer(),
						   __classid(TDarwinetDomainViewImpl),
						   CLSID_DarwinetDomainView,
						   Comobj::ciMultiInstance,
						   Comobj::tmApartment);
}
#pragma startup createFactory 32


IDarwinetSEPSI* STDMETHODCALLTYPE TDarwinetDomainViewImpl::getSEPSI()
{
	LOG_METHOD_SCOPE;
	// Create the Domain COM object and return the interface to it
	if (!this->m_COMIDarwinetSEPSI) {
		m_COMIDarwinetSEPSI = CoDarwinetSEPSI::Create();
	}
	return m_COMIDarwinetSEPSI;
}

