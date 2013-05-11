// ---------------------------------------------------------------------------
// DARWINETDOMAINIMPL : Implementation of TDarwinetDomainImpl (CoClass: DarwinetDomain, Interface: IDarwinetDomain)
// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DarwinetDomainImpl.h"
#include "BusinessLogUnit.h"


// ---------------------------------------------------------------------------
// TDarwinetDomainImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainImpl::TDarwinetDomainImpl()
{
	LOG_METHOD_SCOPE_S(_UTF8sz("()"));
}


// ---------------------------------------------------------------------------
// TDarwinetDomainImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainImpl::TDarwinetDomainImpl(const System::_di_IInterface Controller)
							  : inherited(Controller)
{
	LOG_METHOD_SCOPE_S(_UTF8sz("(const System::_di_IInterface Controller)"));
}


// ---------------------------------------------------------------------------
// TDarwinetDomainImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainImpl::TDarwinetDomainImpl(Comobj::TComObjectFactory* Factory,
									  const System::_di_IInterface Controller)
							  : inherited(Factory, Controller)
{
	LOG_METHOD_SCOPE_S(_UTF8sz("(Comobj::TComObjectFactory* Factory,const System::_di_IInterface Controller)"));
}

void __fastcall TDarwinetDomainImpl::EventSinkChanged(const System::_di_IInterface EventSink)
{
  LOG_METHOD_SCOPE;
  FEvents.Bind(EventSink);
}

// ---------------------------------------------------------------------------
// TDarwinetDomainImpl - Class Factory
// ---------------------------------------------------------------------------
static void createFactory()
{
	LOG_FUNCTION_SCOPE;
  new TCppAutoObjectFactory<TDarwinetDomainImpl>(Comserv::GetComServer(),
						   __classid(TDarwinetDomainImpl),
						   CLSID_DarwinetDomain,
						   Comobj::ciMultiInstance,
						   Comobj::tmApartment);
}
#pragma startup createFactory 32



IDarwinetDomainView* STDMETHODCALLTYPE TDarwinetDomainImpl::getView()
{
	LOG_METHOD_SCOPE;
	// Create the Domain COM object and return the interface to it
	if (!this->m_COMIDarwinetDomainView) {
		m_COMIDarwinetDomainView = CoDarwinetDomainView::Create();
	}
	return m_COMIDarwinetDomainView;
}


