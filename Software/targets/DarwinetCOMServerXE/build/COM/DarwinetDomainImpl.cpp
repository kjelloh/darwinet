// ---------------------------------------------------------------------------
// DARWINETDOMAINIMPL : Implementation of TDarwinetDomainImpl (CoClass: DarwinetDomain, Interface: IDarwinetDomain)
// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DarwinetDomainImpl.h"


// ---------------------------------------------------------------------------
// TDarwinetDomainImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainImpl::TDarwinetDomainImpl()
{
}


// ---------------------------------------------------------------------------
// TDarwinetDomainImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainImpl::TDarwinetDomainImpl(const System::_di_IInterface Controller)
                              : inherited(Controller)
{
}


// ---------------------------------------------------------------------------
// TDarwinetDomainImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainImpl::TDarwinetDomainImpl(Comobj::TComObjectFactory* Factory,
                                      const System::_di_IInterface Controller)
                              : inherited(Factory, Controller)
{
}

void __fastcall TDarwinetDomainImpl::EventSinkChanged(const System::_di_IInterface EventSink)
{
  FEvents.Bind(EventSink);
}

// ---------------------------------------------------------------------------
// TDarwinetDomainImpl - Class Factory
// ---------------------------------------------------------------------------
static void createFactory()
{
  new TCppAutoObjectFactory<TDarwinetDomainImpl>(Comserv::GetComServer(),
                           __classid(TDarwinetDomainImpl),
                           CLSID_DarwinetDomain,
                           Comobj::ciMultiInstance,
                           Comobj::tmApartment);
}
#pragma startup createFactory 32


